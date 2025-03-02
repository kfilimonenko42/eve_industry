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

#ifndef _EVEASSETS_SOLARSYSTEM_HPP_
#define _EVEASSETS_SOLARSYSTEM_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <compare>

#include "Point.hpp"

namespace EVE::Assets
{

	class SolarSystem
	{
	public:
		SolarSystem() = default;

		bool operator==(const SolarSystem& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const SolarSystem& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		std::string m_Name;
		std::string m_NameSearch;
		std::string m_SecurityClass;
		Point m_Center{};
		Point m_Max{};
		Point m_Min{};
		double m_Luminosity{};
		double m_Security{};
		double m_Radius{};
		std::uint32_t m_ID{};
		std::uint32_t m_NameID{};
		std::uint32_t m_RegionID{};
		std::uint32_t m_ConstellationID{};
		std::uint32_t m_SunTypeID{};
		bool m_Border{};
		bool m_Corridor{};
		bool m_Fringe{};
		bool m_Hub{};
		bool m_International{};
		bool m_Regional{};
		bool m_FlagStations{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_SOLARSYSTEM_HPP_