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

#ifndef _EVEASSETS_AGENT_HPP_
#define _EVEASSETS_AGENT_HPP_

#include <cstdint>
#include <compare>

namespace EVE::Assets
{

	class Agent
	{
	public:
		Agent() = default;

		bool operator==(const Agent& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const Agent& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		std::uint32_t m_ID{};
		std::uint32_t m_AgentTypeID{};
		std::uint32_t m_CorporationID{};
		std::uint32_t m_DivisionID{};
		std::uint32_t m_Level{};
		std::uint32_t m_LocationID{};
		bool m_IsLocator{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_AGENT_HPP_