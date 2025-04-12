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

#include <vector>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "BlueprintMaterialEfficiency.hpp"
#include "EnumTools.hpp"
#include "JsonHelper.hpp"
#include "DefaultSettings.hpp"

namespace EVE::Assets
{

	class BlueprintSettings
	{
	public:
		BlueprintSettings() = default;

	public:
		std::uint32_t m_ID{};
		std::uint32_t m_SolarSystemID{};
		EVE::Assets::BlueprintME m_BpME{ EVE::Assets::BlueprintME::ME_0 };
		EVE::Assets::StructureME m_StructME{ EVE::Assets::StructureME::ME_0 };
		EVE::Assets::RigME m_RigME{ EVE::Assets::RigME::NO_RIG };
		std::uint64_t m_Weight{};
		std::uint64_t m_MaxRuns{};
		double m_StructureRoleBonus{ 0.03 };
		double m_FacilityTax{ 0.01 };
	};

	[[nodiscard]] inline nlohmann::json to_json(const BlueprintSettings& bps)
	{
		return nlohmann::json{
			{"id", bps.m_ID},
			{"solar_system", bps.m_SolarSystemID},
			{"me", stringFromEnum(EVE::Assets::arrBlueprintME, bps.m_BpME)},
			{"me_struct", stringFromEnum(EVE::Assets::arrStructureME, bps.m_StructME)},
			{"me_rig", stringFromEnum(EVE::Assets::arrRigME, bps.m_RigME)},
			{"weight", bps.m_Weight},
			{"maximum_runs", bps.m_MaxRuns},
			{"structure_role_bonus", bps.m_StructureRoleBonus},
			{"facility_tax", bps.m_FacilityTax}
		};
	}

	inline void saveUserBlueprintSettings(const std::vector<BlueprintSettings>& src)
	{
		nlohmann::json result = nlohmann::json::array();

		for (const auto& element : src)
		{
			result.push_back(to_json(element));
		}

		JsonHelper jhelper(std::filesystem::current_path().string() + EVE::APPSETTINGS::Paths::BlueprintsSettings_Users);
		jhelper.save(result);
	}

	inline void updateUserBlueprintSettings(std::vector<BlueprintSettings>& container,
		const std::uint32_t bp_id, const std::uint32_t solSystem_id,
		const EVE::Assets::BlueprintME bpME, const EVE::Assets::StructureME structME, const EVE::Assets::RigME rigME,
		const std::uint64_t maxRuns, const double structureRoleBonus, const double facilityTax)
	{
		auto ittr = std::find_if(std::begin(container), std::end(container),
			[bp_id](const BlueprintSettings& element)
			{
				return element.m_ID == bp_id;
			});

		if (ittr != std::end(container))
		{
			ittr->m_SolarSystemID = solSystem_id;
			ittr->m_BpME = bpME;
			ittr->m_StructME = structME;
			ittr->m_RigME = rigME;
			ittr->m_MaxRuns = maxRuns;
			ittr->m_StructureRoleBonus = structureRoleBonus;
			ittr->m_FacilityTax = facilityTax;
		}
	}

} // namespace EVE::Assets

#endif // _EVEASSETS_BLUEPRINTSETTINGS_HPP_