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

#include "JsonIndustrySaver.hpp"
#include "JsonHelper.hpp"
#include "Version.hpp"
#include "ProductionStage.hpp"
#include "BlueprintRecord.hpp"
#include "EnumTools.hpp"

void EVE::Industry::JsonIndustrySaver::save(const std::string& fileName, const IndustryProject& source)
{
	nlohmann::json typesProject = nlohmann::json::array();
	prepareDataJson(source.m_TypesProject, typesProject);

	nlohmann::json stock = nlohmann::json::array();
	prepareDataJson(source.m_Stock, stock);

	nlohmann::json blueprintsProject = nlohmann::json::array();
	prepareDataJson(source.m_BlueprintsList, blueprintsProject, source.m_BPME);
	
	nlohmann::json typesRaw = nlohmann::json::array();
	prepareDataJson(source.m_TypesBase, typesRaw);

	nlohmann::json typesBps = nlohmann::json::array();
	prepareDataJson(source.m_TypesBlueprint, typesBps);

	nlohmann::json stages = nlohmann::json::array();
	prepareDataJson(source.m_ProductionStages, stages);

	nlohmann::json json;
	json["types_project"] = typesProject;
	json["available_items"] = stock;
	json["blueprints_project"] = blueprintsProject;
	json["types_raw"] = typesRaw;
	json["types_bps"] = typesBps;
	json["stages"] = stages;
	json["name"] = source.name();
	json["version"] = VERSION_NUMBER;

	JsonHelper jhelper(fileName);
	jhelper.save(json);
}

nlohmann::json EVE::Industry::nlohmann_to_json(const MaterialProject& elem)
{
	return nlohmann::json{
		{"id", elem.m_Type.id()},
		{"quantity", elem.m_Type.getQuantity()}
	};
}

nlohmann::json EVE::Industry::nlohmann_to_json(const BlueprintProject& elem, const std::unordered_map<std::uint32_t, EVE::Assets::BlueprintMaterialEfficiency>& bpme)
{
	auto current_bpme = getBlueprintMaterialEfficiency(elem.m_Blueprint.id(), bpme);

	return nlohmann::json{
		{"id", elem.m_Blueprint.id()},
		{"solar_system", elem.m_SolarSystem.id()},
		{"maximum_runs", elem.m_MaxRunsPerJob},
		{"me", stringFromEnum(EVE::Assets::arrBlueprintME, current_bpme.m_BpME)},
		{"me_struct", stringFromEnum(EVE::Assets::arrStructureME, current_bpme.m_StructME)},
		{"me_rig", stringFromEnum(EVE::Assets::arrRigME, current_bpme.m_RigME)}
	};
}

nlohmann::json EVE::Industry::nlohmann_to_json(const MaterialBase& elem)
{
	return nlohmann::json{
		{"id", elem.m_Type.id()},
		{"quantity", elem.m_Type.getQuantity()}
	};
}

nlohmann::json EVE::Industry::nlohmann_to_json(const MaterialBlueprint& elem)
{
	return nlohmann::json{
		{"type_id", elem.m_Type.id()},
		{"bp_id", elem.m_Blueprint.id()},
		{"quantity", elem.m_Type.getQuantity()}
	};
}

nlohmann::json EVE::Industry::nlohmann_to_json(const ProductionStage& elem)
{
	return nlohmann::json{
		{"stage", elem.m_Stage},
		{"id", elem.m_Blueprint.id()},
		{"runs", elem.m_Runs},
		{"status", stringFromEnum(arrStageStatus, elem.m_Status)}
	};
}
