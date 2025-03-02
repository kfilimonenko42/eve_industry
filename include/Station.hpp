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

#ifndef _EVEASSETS_STATION_HPP_
#define _EVEASSETS_STATION_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <compare>

#include "Point.hpp"

namespace EVE::Assets
{

	class Station
	{
	public:
		Station() = default;

		bool operator==(const Station& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const Station& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		std::string m_Name;
		std::string m_NameSearch;
		Point m_Position{};
		double m_ReprocessingEfficiency{};
		double m_ReprocessingStationsTake{};
		double m_Security{};
		std::uint32_t m_ID{};
		std::uint32_t m_StationTypeID{};
		std::uint32_t m_RegionID{};
		std::uint32_t m_ConstellationID{};
		std::uint32_t m_SolarSystemID{};
		std::uint32_t m_CorporationID{};
		std::uint32_t m_DockingCostPerVolume{};
		std::uint32_t m_MaxShipVolumeDockable{};
		std::uint32_t m_OfficeRentalCost{};
		std::uint32_t m_OperationID{};
		std::uint32_t m_ReprocessingHangarFlag{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_STATION_HPP_