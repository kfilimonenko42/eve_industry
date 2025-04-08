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

#ifndef _EVEINDUSTRY_APPRAISALCONTAINER_HPP_
#define _EVEINDUSTRY_APPRAISALCONTAINER_HPP_

#include <cstdint>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <utility>
#include <tuple>
#include <string>
#include <format>
#include <functional>
#include <chrono>

#include "TypePrice.hpp"
#include "Appraisal.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "UpdateContainerThread.hpp"
#include "ChronoTools.hpp"

namespace EVE::Industry
{
	constexpr static double PRICE_CACHED_TIME_TEST = 3600.0;

	struct UpdatePriceRecord
	{
		UpdatePriceRecord(int owner_id, std::uint32_t typeId, const EsiOrderSettings& esiSettings)
			: m_EsiSettings{ esiSettings }, m_OwnerId{ owner_id }, m_TypeId{ typeId }
		{
		}

		EsiOrderSettings m_EsiSettings{};
		int m_OwnerId{};
		std::uint32_t m_TypeId{};
	};

	bool thread_price_check(const UpdatePriceRecord& updRecord);

	class AppraisalContainer
	{
	public:
		// [areaID].[type_id]->[TypePrice]
		using umapPrices = std::unordered_map<std::uint32_t, std::unordered_map<std::uint32_t, TypePrice>>;
		// [areaID]->set([type_id])
		using umapQueue = std::unordered_map<std::uint32_t, std::set<std::uint32_t>>;
		// update thread
		using updThread = UpdateContainerThread<UpdatePriceRecord>;
		AppraisalContainer() = default;

		static AppraisalContainer& Instance();

		void clear();
		void addInQueueIfNeed(const UpdatePriceRecord& updRecord);
		TypePrice getPriceNoUpdate(const UpdatePriceRecord& updRecord);
		bool check(const UpdatePriceRecord& updRecord);
		time_point lastUpdate(int owner_id);

	private:
		bool hasPrice(const UpdatePriceRecord& updRecord) const;
		bool needUpdate(const UpdatePriceRecord& updRecord) const;
		bool do_check(const UpdatePriceRecord& updRecord);
		void storePrice(const UpdatePriceRecord& updRecord, const double sellPrice, const double buyPrice);
		bool inQueue(const UpdatePriceRecord& updRecord) const;
		void addInQueue(const UpdatePriceRecord& updRecord);

	private:
		umapPrices m_Container;
		umapQueue m_InQueue;
		std::function<bool(const UpdatePriceRecord&)> checkPriceFunc = thread_price_check;
		updThread m_UpdThread{ checkPriceFunc };
	};

	inline double priceSell(const UpdatePriceRecord& updRecord, std::uint32_t count = 1)
	{
		auto& container = AppraisalContainer::Instance();
		const auto& price = container.getPriceNoUpdate(updRecord);
		return price.m_PriceSell * count;
	}

	inline double priceBuy(const UpdatePriceRecord& updRecord, std::uint32_t count = 1)
	{
		auto& container = AppraisalContainer::Instance();
		const auto& price = container.getPriceNoUpdate(updRecord);
		return price.m_PriceBuy * count;
	}

	inline std::string priceSellToString(const UpdatePriceRecord& updRecord, std::uint32_t count = 1)
	{
		return std::format(std::locale(""), "{:.2Lf}", priceSell(updRecord, count));
	}

	inline std::string priceBuyToString(const UpdatePriceRecord& updRecord, std::uint32_t count = 1)
	{
		return std::format(std::locale(""), "{:.2Lf}", priceBuy(updRecord, count));
	}

	inline bool priceUpdOwner(int owner_id, time_point last)
	{
		auto& container = AppraisalContainer::Instance();
		time_point time = container.lastUpdate(owner_id);
		return time > last;
	}

} // EVE::Industry

#endif // _EVEINDUSTRY_APPRAISALCONTAINER_HPP_