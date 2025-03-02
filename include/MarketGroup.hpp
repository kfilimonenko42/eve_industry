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

#ifndef _EVEASSETS_MARKETGROUP_HPP_
#define _EVEASSETS_MARKETGROUP_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <compare>
#include <compare>

namespace EVE::Assets
{

	class MarketGroup
	{
	public:
		MarketGroup() = default;
		MarketGroup(std::uint32_t _id, std::uint32_t _parentid, std::string _name);

		bool operator==(const MarketGroup& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const MarketGroup& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		std::string m_Name;
		std::uint32_t m_ID{};
		std::uint32_t m_ParentID{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_MARKETGROUP_HPP_