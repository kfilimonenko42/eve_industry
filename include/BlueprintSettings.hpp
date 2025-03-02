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

#ifndef _EVEASSETS_BLUEPRINTSETTINGS_HPP_
#define _EVEASSETS_BLUEPRINTSETTINGS_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <algorithm>
#include <cmath>

#include "BlueprintMaterialEfficiency.hpp"

namespace EVE::Assets
{

	class BlueprintSettings
	{
	public:
		BlueprintSettings() = default;

	public:
		std::uint32_t m_ID{};
		EVE::Assets::BlueprintME m_BpME{ EVE::Assets::BlueprintME::ME_0 };
		EVE::Assets::StructureME m_StructME{ EVE::Assets::StructureME::ME_0 };
		EVE::Assets::RigME m_RigME{ EVE::Assets::RigME::NO_RIG };
		std::uint64_t m_Weight{};
		std::uint64_t m_MaxRuns{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_BLUEPRINTSETTINGS_HPP_