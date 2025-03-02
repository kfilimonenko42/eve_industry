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

#ifndef _EVEASSETS_TYPE_HPP_
#define _EVEASSETS_TYPE_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <compare>
#include <set>

namespace EVE::Assets
{

	class Type
	{
	public:
		Type() = default;

		bool operator==(const Type& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const Type& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		std::string m_Name;
		std::string m_NameSearch;
		std::string m_Description;
		float m_BasePrice{};
		float m_Mass{};
		float m_Capacity{};
		double m_Volume{};
		double m_PackagedVolume{};
		std::uint32_t m_ID{};
		std::uint32_t m_BlueprintID{};
		std::uint32_t m_IconID{};
		std::uint32_t m_MarketGroupID{};
		std::uint32_t m_GroupID{};
		std::uint32_t m_CategoryID{};
	};

	struct IsTypePI
	{
		bool operator()(const uint32_t type_id)
		{
			return m_PIgroups.contains(type_id);
		}

	private:
		const std::set<int> m_PIgroups{ 1032, 1034, 1040, 1041, 1042 };
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_TYPE_HPP_