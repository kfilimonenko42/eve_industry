/*
	EVE bulk indy
	Copyright (C) 2025 Kirill Filimonenko

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "AppraisalContainer.hpp"

#include "Assets.hpp"
#include "Order.hpp"
#include "JsonAssetsLoader.hpp"
#include "JsonHelper.hpp"

bool EVE::Industry::thread_price_check(const UpdatePriceRecord& updRecord)
{
	AppraisalContainer& container = AppraisalContainer::Instance();
	return container.check(updRecord);
}

EVE::Industry::AppraisalContainer& EVE::Industry::AppraisalContainer::Instance()
{
	static AppraisalContainer instance{};
	return instance;
}

void EVE::Industry::AppraisalContainer::clear()
{
	m_Container.clear();
}

void EVE::Industry::AppraisalContainer::addInQueueIfNeed(const UpdatePriceRecord& updRecord)
{
	if (needUpdate(updRecord))
	{
		if (!inQueue(updRecord))
		{
			addInQueue(updRecord);
			m_UpdThread.push(updRecord);
		}
	}
}

EVE::Industry::TypePrice EVE::Industry::AppraisalContainer::getPriceNoUpdate(const UpdatePriceRecord& updRecord)
{
	if (hasPrice(updRecord))
	{
		const std::uint32_t areaID = updRecord.m_EsiSettings.saveID();
		const std::uint32_t typeID = updRecord.m_TypeId;

		return m_Container.at(areaID).at(typeID);
	}

	return TypePrice{};
}

bool EVE::Industry::AppraisalContainer::check(const UpdatePriceRecord& updRecord)
{
	if (needUpdate(updRecord))
	{
		return do_check(updRecord);
	}
	return false;
}

time_point EVE::Industry::AppraisalContainer::lastUpdate(int owner_id)
{
	return m_UpdThread.lastUpdate(owner_id);
}

bool EVE::Industry::AppraisalContainer::hasPrice(const UpdatePriceRecord& updRecord) const
{
	return !needUpdate(updRecord);
}

bool EVE::Industry::AppraisalContainer::needUpdate(const UpdatePriceRecord& updRecord) const
{
	const std::uint32_t areaID = updRecord.m_EsiSettings.saveID();

	if (!m_Container.contains(areaID))
	{
		return true;
	}

	const std::uint32_t typeID = updRecord.m_TypeId;
	return !m_Container.at(areaID).contains(typeID);
}

bool EVE::Industry::AppraisalContainer::do_check(const UpdatePriceRecord& updRecord)
{
	EsiPrice priceChecker(updRecord.m_TypeId, updRecord.m_EsiSettings);

	try
	{
		const auto priceInfo = priceChecker.get();
		const bool isSuccess = std::get<0>(priceInfo);
		if (isSuccess)
		{
			storePrice(updRecord, std::get<1>(priceInfo), std::get<2>(priceInfo));
		}
		return isSuccess;
	}
	catch (const std::runtime_error& er)
	{
		Log::LOG_ERROR(std::format("update price for type: {} ({})", updRecord.m_TypeId, er.what()));
		return false;
	}
}

void EVE::Industry::AppraisalContainer::storePrice(
	const UpdatePriceRecord& updRecord,
	const double sellPrice,
	const double buyPrice)
{
	const std::uint32_t areaID = updRecord.m_EsiSettings.saveID();
	const std::uint32_t typeID = updRecord.m_TypeId;

	if (typeID == 0)
	{
		return;
	}

	m_Container[areaID].emplace(typeID, TypePrice{ sellPrice , buyPrice });
}

bool EVE::Industry::AppraisalContainer::inQueue(const UpdatePriceRecord& updRecord) const
{
	const std::uint32_t areaID = updRecord.m_EsiSettings.saveID();
	const std::uint32_t typeID = updRecord.m_TypeId;

	return m_InQueue.contains(areaID) && m_InQueue.at(areaID).contains(typeID);
}

void EVE::Industry::AppraisalContainer::addInQueue(const UpdatePriceRecord& updRecord)
{
	const std::uint32_t areaID = updRecord.m_EsiSettings.saveID();
	const std::uint32_t typeID = updRecord.m_TypeId;

	m_InQueue[areaID].emplace(typeID);
}
