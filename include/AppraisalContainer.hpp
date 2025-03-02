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
#include <mutex>
#include <algorithm>
#include <tuple>

#include "TypePrice.hpp"
#include "Appraisal.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "Response.hpp"

namespace EVE::Industry
{
	constexpr static double PRICE_CACHED_TIME = 3600.0;

	class AppraisalContainer
	{
	public:
		using umapPrices = std::unordered_map<std::uint32_t, std::unordered_map<std::uint32_t, TypePrice>>;

		AppraisalContainer() = default;

		static AppraisalContainer& Instance();

		void clear();
		bool needUpdate(const std::uint32_t id, const EsiOrderSettings& esiSettings) const;
		bool hasPrice(const std::uint32_t id, const EsiOrderSettings& esiSettings) const;
		[[nodiscard]] TypePrice getPrice(const std::uint32_t id, const EsiOrderSettings& esiSettings) const;

		bool push(const std::uint32_t id, const EsiOrderSettings& esiSettings);

	private:
		bool do_check(const std::uint32_t id, const EsiOrderSettings& esiSettings);
		void storePrice(const std::uint32_t id, const double sellPrice, const double buyPrice, const EsiOrderSettings& esiSettings);

	private:
		umapPrices m_Container;
		std::mutex m_Mutex;
	};


} // EVE::Industry

#endif // _EVEINDUSTRY_APPRAISALCONTAINER_HPP_