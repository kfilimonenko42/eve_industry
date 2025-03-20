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

#ifndef _EVEASSETS_SYSTEMCOSTINDICIES_HPP_
#define _EVEASSETS_SYSTEMCOSTINDICIES_HPP_

#include <cstdint>
#include <compare>

#include "SolarSystem.hpp"

namespace EVE::Assets
{

	class SystemCostIndices
	{
	public:
		SystemCostIndices() = default;

		bool operator==(const SystemCostIndices& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const SystemCostIndices& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		double m_Manufacturing{};
		double m_Reaction{};
		double m_ResearchTimeEfficiency{};
		double m_ResearchMaterialEfficiency{};
		double m_Copying{};
		double m_Invention{};
		std::uint32_t m_ID{};
	};

}

#endif // _EVEASSETS_SYSTEMCOSTINDICIES_HPP_