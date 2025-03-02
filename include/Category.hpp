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

#ifndef _EVEASSETS_CATEGORY_HPP_
#define _EVEASSETS_CATEGORY_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <compare>

namespace EVE::Assets
{

	class Category
	{
	public:
		Category() = default;
		Category(std::uint32_t _id, std::string _name);

		bool operator==(const Category& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const Category& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		std::string m_Name;
		std::uint32_t m_ID{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_CATEGORY_HPP_