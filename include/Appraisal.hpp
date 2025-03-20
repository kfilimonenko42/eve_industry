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

#ifndef _EVEINDUSTRY_APPRAISAL_HPP_
#define _EVEINDUSTRY_APPRAISAL_HPP_

#include <optional>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdint>
#include <ranges>
#include <numeric>

#include "Assets.hpp"
#include "Order.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "EsiOrderSettings.hpp"

namespace EVE::Industry
{
    

    class EsiPrice
    {
    public:
        using Order = EVE::Assets::Order;
        using OrdersContainer = EVE::Assets::OrdersContainer;
        using SellBuy = std::tuple<bool, double, double>;

        explicit EsiPrice(
            const std::uint32_t type_id,
            const EsiOrderSettings& esiSettings);

        SellBuy get();

    private:
        double getSellPrice(OrdersContainer& orders) const;
        double getBuyPrice(OrdersContainer& orders) const;

    private:
        std::uint32_t m_TypeID{};
        EsiOrderSettings m_EsiSettings{};
    };

} //

#endif // _EVEINDUSTRY_APPRAISAL_HPP_