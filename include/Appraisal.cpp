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

#include "Appraisal.hpp"
#include "ESI.hpp"

EVE::Industry::EsiPrice::EsiPrice(
	const std::uint32_t type_id,
	const EsiOrderSettings& esiSettings)
	: m_TypeID{ type_id }, m_EsiSettings{ esiSettings }
{
}

EVE::Industry::EsiPrice::SellBuy EVE::Industry::EsiPrice::get()
{
	RestAPI::Response response = ESI::getOrders(m_EsiSettings.m_RegionID, m_TypeID);
	if (!response.m_Successful)
	{
		return std::make_tuple( false, 0.0, 0.0 );
	}
	
	EVE::Assets::OrdersContainer orders;
	orders.load(std::make_unique<EVE::Assets::JsonLoader>(std::move(response.m_Result)));
	if (orders.empty())
	{
		return std::make_tuple( false, 0.0, 0.0);
	}

	return std::make_tuple(
		true,
		getSellPrice(orders),
		getBuyPrice(orders));
}

double EVE::Industry::EsiPrice::getSellPrice(OrdersContainer& orders) const
{
	auto filterSellOrders = std::views::filter(
		[esi = m_EsiSettings](const Order& order)
		{
			if (esi.m_StationID > 0)
			{
				return order.m_LocationID == esi.m_StationID && !order.m_IsBuyOrder;
			}
			else if (esi.m_SolarSystemID > 0)
			{
				return order.m_SystemID == esi.m_SolarSystemID && !order.m_IsBuyOrder;
			}
			{
				return !order.m_IsBuyOrder;
			}
		});

	auto filteredSellOrders = orders.get_container() | filterSellOrders;

	if (filteredSellOrders.empty())
	{
		return 0.0;
	}

	const auto& min = std::ranges::min(filteredSellOrders,
		[](const Order& order1, const Order& order2)
		{
			return order1.m_Price < order2.m_Price;
		});

	return min.m_Price;
}

double EVE::Industry::EsiPrice::getBuyPrice(OrdersContainer& orders) const
{
	auto filterBuyOrders = std::views::filter(
		[esi = m_EsiSettings](const Order& order)
		{
			if (esi.m_StationID > 0)
			{
				return order.m_LocationID == esi.m_StationID && order.m_IsBuyOrder;
			}
			else if (esi.m_SolarSystemID > 0)
			{
				return order.m_SystemID == esi.m_SolarSystemID && order.m_IsBuyOrder;
			}
			{
				return order.m_IsBuyOrder;
			}
		});

	auto filteredBuyOrders = orders.get_container() | filterBuyOrders;

	if (filteredBuyOrders.empty())
	{
		return 0.0;
	}

	const auto& max = std::ranges::max(filteredBuyOrders,
		[](const Order& order1, const Order& order2)
		{
			return order1.m_Price < order2.m_Price;
		});

	return max.m_Price;
}