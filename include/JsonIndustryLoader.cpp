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

#include "JsonIndustryLoader.hpp"
#include "Assets.hpp"
#include "TypeRecord.hpp"
#include "BlueprintRecord.hpp"
#include "SolarSystemRecord.hpp"
#include "EnumTools.hpp"

void EVE::Industry::JsonIndustryLoader::load(const std::string& fileName, IndustryProject& dst)
{
	clearProject(dst);

	JsonHelper jhelper(fileName);
	nlohmann::json json;
	if (!jhelper.load(json))
	{
		return;
	}

	if (json.contains("name"))
	{
		dst.setName(json["name"]);
	}
	else
	{
		dst.setName("noname");
	}
		
	try
	{
		readMaterialsProject(json, dst.m_TypesProject);
		readStock(json, dst.m_Stock);
		readBlueprintsProject(json, dst);
		readTypesRaw(json, dst.m_TypesBase);
		readTypesBps(json, dst.m_TypesBlueprint);
		readStages(json, dst.m_ProductionStages);
	}
	catch (const std::exception& ex)
	{
		Log::LOG_ERROR(ex.what());
	}
}

void EVE::Industry::JsonIndustryLoader::clearProject(IndustryProject& dst)
{
	dst.clear();
}

void EVE::Industry::JsonIndustryLoader::readMaterialsProject(const nlohmann::json& src, ListDataWrapper<MaterialProject>& dst)
{
	const Assets& assets = Assets::Instance();

	if (!src.contains("types_project"))
	{
		return;
	}
	
	std::vector<MaterialProject> tmp;
	const auto& materials_part = src["types_project"];
	for (auto& elem : materials_part)
	{
		if (!elem.contains("id") || !elem.contains("quantity"))
		{
			continue;
		}

		std::uint32_t type_id{};
		elem.at("id").get_to(type_id);

		std::uint64_t quantity{};
		elem.at("quantity").get_to(quantity);

		try
		{
			tmp.emplace_back(TypeRecord{ type_id }, quantity);
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}

	dst.update(std::move(tmp));
}

void EVE::Industry::JsonIndustryLoader::readStock(const nlohmann::json& src, ListDataWrapper<MaterialProject>& dst)
{
	const Assets& assets = Assets::Instance();

	if (!src.contains("available_items"))
	{
		return;
	}

	std::vector<MaterialProject> tmp;
	const auto& materials_part = src["available_items"];
	for (auto& elem : materials_part)
	{
		if (!elem.contains("id") || !elem.contains("quantity"))
		{
			continue;
		}

		std::uint32_t type_id{};
		elem.at("id").get_to(type_id);

		std::uint64_t quantity{};
		elem.at("quantity").get_to(quantity);

		try
		{
			tmp.emplace_back(TypeRecord{ type_id }, quantity);
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}

	dst.update(std::move(tmp));
}

void EVE::Industry::JsonIndustryLoader::readBlueprintsProject(const nlohmann::json& src, IndustryProject& dst)
{
	const Assets& assets = Assets::Instance();

	if (!src.contains("blueprints_project"))
	{
		return;
	}

	auto& blueprints_part = src["blueprints_project"];
	std::vector<BlueprintProject> tmp_bp;
	for (auto& elem : blueprints_part)
	{
		if (!elem.contains("id"))
		{
			continue;
		}

		std::uint32_t bp_id{};
		elem.at("id").get_to(bp_id);

		std::uint32_t solar_system_id{};
		if (elem.contains("solar_system"))
		{
			elem.at("solar_system").get_to(solar_system_id);
		}

		std::uint64_t maximum_runs{};
		if (elem.contains("maximum_runs"))
		{
			elem.at("maximum_runs").get_to(maximum_runs);
		}

		std::string str_me{};
		if (elem.contains("me"))
		{
			elem.at("me").get_to(str_me);
		}

		std::string str_struct_me{};
		if (elem.contains("me_struct"))
		{
			elem.at("me_struct").get_to(str_struct_me);
		}

		std::string str_rig_me{};
		if (elem.contains("me_rig"))
		{
			elem.at("me_rig").get_to(str_rig_me);
		}

		EVE::Assets::BlueprintME me;
		enumFromString(EVE::Assets::arrBlueprintME, str_me, me);
		EVE::Assets::StructureME struct_me;
		enumFromString(EVE::Assets::arrStructureME, str_struct_me, struct_me);
		EVE::Assets::RigME rig_me;
		enumFromString(EVE::Assets::arrRigME, str_rig_me, rig_me);

		SolarSystemRecord solSystem;
		if (solar_system_id > 0)
		{
			try
			{
				solSystem = SolarSystemRecord{ solar_system_id };
				dst.m_BPSystem[bp_id] = solSystem;
			}
			catch (const std::runtime_error& er)
			{
				Log::LOG_ERROR(er.what());
			}
		}

		try
		{
			tmp_bp.emplace_back(BlueprintRecord{ bp_id }, std::forward<SolarSystemRecord>(solSystem),
				EVE::Assets::BlueprintMaterialEfficiency{ me, struct_me, rig_me },
				maximum_runs);
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
		
		dst.m_BPME[bp_id] = EVE::Assets::BlueprintMaterialEfficiency{ me, struct_me, rig_me };
		if (maximum_runs > 0)
		{
			dst.m_BPMaxRunsPreJob[bp_id] = maximum_runs;
		}
	}

	dst.m_BlueprintsList.update(std::move(tmp_bp));
}

void EVE::Industry::JsonIndustryLoader::readTypesRaw(const nlohmann::json& src, ListDataWrapper<MaterialBase>& dst)
{
	const Assets& assets = Assets::Instance();

	if (!src.contains("types_raw"))
	{
		return;
	}

	auto& blueprints_part = src["types_raw"];
	std::vector<MaterialBase> tmp;
	for (auto& elem : blueprints_part)
	{
		if (!elem.contains("id") || !elem.contains("quantity"))
		{
			continue;
		}

		std::uint32_t type_id{};
		elem.at("id").get_to(type_id);

		std::uint64_t quantity{};
		elem.at("quantity").get_to(quantity);

		try
		{
			tmp.emplace_back(TypeRecord(type_id), quantity);
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}

	std::sort(std::begin(tmp), std::end(tmp), MaterialsBaseSortByGroupIdTypeName());
	dst.update(std::move(tmp));
}

void EVE::Industry::JsonIndustryLoader::readTypesBps(const nlohmann::json& src, ListDataWrapper<MaterialBlueprint>& dst)
{
	const Assets& assets = Assets::Instance();

	if (!src.contains("types_bps"))
	{
		return;
	}

	auto& blueprints_part = src["types_bps"];
	std::vector<MaterialBlueprint> tmp;
	for (auto& elem : blueprints_part)
	{
		if (!elem.contains("type_id") || !elem.contains("bp_id") || !elem.contains("quantity"))
		{
			continue;
		}

		std::uint32_t type_id{};
		elem.at("type_id").get_to(type_id);

		std::uint32_t bp_id{};
		elem.at("bp_id").get_to(bp_id);

		std::uint64_t quantity{};
		elem.at("quantity").get_to(quantity);

		try
		{
			tmp.emplace_back(BlueprintRecord{ bp_id }, TypeRecord{ type_id }, quantity);
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}

	std::sort(std::begin(tmp), std::end(tmp), MaterialsBlueprintSortByWeightName());
	dst.update(std::move(tmp));
}

void EVE::Industry::JsonIndustryLoader::readStages(const nlohmann::json& src, ListDataWrapper<ProductionStage>& dst)
{
	const Assets& assets = Assets::Instance();

	if (!src.contains("stages"))
	{
		return;
	}

	auto& blueprints_part = src["stages"];
	std::vector<ProductionStage> tmp;
	for (auto& elem : blueprints_part)
	{
		if (!elem.contains("id") || !elem.contains("stage") || !elem.contains("runs") || !elem.contains("status"))
		{
			continue;
		}

		std::uint32_t stage{};
		elem.at("stage").get_to(stage);

		std::uint64_t runs{};
		elem.at("runs").get_to(runs);

		std::uint32_t bp_id{};
		elem.at("id").get_to(bp_id);

		std::string str_status;
		elem.at("status").get_to(str_status);
		StageStatus status;
		enumFromString(arrStageStatus, str_status, status);

		try
		{
			tmp.emplace_back(stage, BlueprintRecord{ bp_id }, runs, status);
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}

	std::sort(std::begin(tmp), std::end(tmp), std::less());
	dst.update(std::move(tmp));
}
