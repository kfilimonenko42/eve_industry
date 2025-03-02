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

EVE::Industry::AppraisalContainer& EVE::Industry::AppraisalContainer::Instance()
{
	static AppraisalContainer instance{};
	return instance;
}

void EVE::Industry::AppraisalContainer::clear()
{
	std::scoped_lock sl(m_Mutex);

	m_Container.clear();
}

bool EVE::Industry::AppraisalContainer::needUpdate(const std::uint32_t id, const EsiOrderSettings& esiSettings) const
{
	const std::uint32_t areaID = esiSettings.saveID();

	if (!m_Container.contains(areaID))
	{
		return true;
	}

	return !m_Container.at(areaID).contains(id);
}

bool EVE::Industry::AppraisalContainer::hasPrice(const std::uint32_t id, const EsiOrderSettings& esiSettings) const
{
	const std::uint32_t areaID = esiSettings.saveID();

	if (!m_Container.contains(areaID))
	{
		return false;
	}

	return m_Container.at(areaID).contains(id);
}

void EVE::Industry::AppraisalContainer::storePrice(
	const std::uint32_t id,
	const double sellPrice,
	const double buyPrice,
	const EsiOrderSettings& esiSettings)
{
	if (id == 0)
	{
		return;
	}

	std::scoped_lock sl(m_Mutex);

	const std::uint32_t areaID = esiSettings.saveID();
	m_Container[areaID].emplace(id, TypePrice{sellPrice , buyPrice});
}

EVE::Industry::TypePrice EVE::Industry::AppraisalContainer::getPrice(const std::uint32_t id, const EsiOrderSettings& esiSettings) const
{
	const std::uint32_t areaID = esiSettings.saveID();

	if (m_Container.contains(areaID))
	{
		if (m_Container.at(areaID).contains(id))
		{
			return m_Container.at(areaID).at(id);
		}
	}

	return TypePrice{};
}

bool EVE::Industry::AppraisalContainer::push(const std::uint32_t id, const EsiOrderSettings& esiSettings)
{
	if (id == 0)
	{
		return false;
	}

	return do_check(id, esiSettings);
}

bool EVE::Industry::AppraisalContainer::do_check(const std::uint32_t id, const EsiOrderSettings& esiSettings)
{
	AppraisalContainer& _container = AppraisalContainer::Instance();

	if (_container.needUpdate(id, esiSettings))
	{
		EsiPrice priceChecker(id, esiSettings);

		try
		{
			const auto priceInfo = priceChecker.get();
			const bool isSuccess = std::get<0>(priceInfo);
			if (isSuccess)
			{
				_container.storePrice(id, std::get<1>(priceInfo), std::get<2>(priceInfo), esiSettings);
			}
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(std::format("update price for type: {} ({})", id, er.what()));
			return false;
		}
	}

	return true;
}
