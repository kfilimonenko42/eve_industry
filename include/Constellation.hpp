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

#ifndef _EVEASSETS_CONSTELLATION_HPP_
#define _EVEASSETS_CONSTELLATION_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <compare>

#include "Point.hpp"

namespace EVE::Assets
{

	class Constellation
	{
	public:
		Constellation() = default;

		bool operator==(const Constellation& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const Constellation& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		std::string m_Name;
		EVE::Assets::Point m_Center{};
		EVE::Assets::Point m_Max{};
		EVE::Assets::Point m_Min{};
		double m_Radius{};
		std::uint32_t m_ID{};
		std::uint32_t m_NameID{};
		std::uint32_t m_RegionID{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_CONSTELLATION_HPP_