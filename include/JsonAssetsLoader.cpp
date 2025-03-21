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

#include "JsonAssetsLoader.hpp"

#include "Agent.hpp"
#include "Constellation.hpp"
#include "Region.hpp"
#include "SolarSystem.hpp"
#include "Station.hpp"
#include "Point.hpp"

#include "StringTools.hpp"
#include "EnumTools.hpp"

EVE::Assets::JsonLoader::JsonLoader(std::string&& source)
	: m_Source{ std::move(source) }
{
}

void EVE::Assets::JsonLoader::load(std::vector<Agent>& _container)
{
	json_load(Setting::Paths::Agents, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<Constellation>& _container)
{
	json_load(Setting::Paths::Constellations, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<Region>& _container)
{
	json_load(Setting::Paths::Regions, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<SolarSystem>& _container)
{
	json_load(Setting::Paths::SolarSystems, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<Station>& _container)
{
	json_load(Setting::Paths::Stations, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<Blueprint>& _container)
{
	json_load(Setting::Paths::Blueprints, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<BlueprintSettings>& _container)
{
	json_load(Setting::Paths::BlueprintsSettings, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<Type>& _container)
{
	json_load(Setting::Paths::Types, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<MarketGroup>& _container)
{
	json_load(Setting::Paths::MarketGroups, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<Group>& _container)
{
	json_load(Setting::Paths::Groups, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<Category>& _container)
{
	json_load(Setting::Paths::Categories, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<PI>& _container)
{
	json_load(Setting::Paths::PISchemas, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<Order>& _container)
{
	assert(!m_Source.empty());

	nlohmann::json js;
	try
	{
		js = nlohmann::json::parse(m_Source);
	}
	catch (const std::runtime_error& er)
	{
		Log::LOG_ERROR(er.what());
	}
	json_load(js, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<SystemCostIndices>& _container)
{
	assert(!m_Source.empty());

	nlohmann::json js;
	try
	{
		js = nlohmann::json::parse(m_Source);
	}
	catch (const std::runtime_error& er)
	{
		Log::LOG_ERROR(er.what());
	}
	json_load(js, _container);
}

void EVE::Assets::JsonLoader::load(std::vector<MarketPrice>& _container)
{
	assert(!m_Source.empty());

	nlohmann::json js;
	try
	{
		js = nlohmann::json::parse(m_Source);
	}
	catch (const std::runtime_error& er)
	{
		Log::LOG_ERROR(er.what());
	}
	json_load(js, _container);
}

void EVE::Assets::from_json(const nlohmann::json& j, Agent& v)
{
	if (!j.contains("agentID")) { throw std::runtime_error("agentID is not found."); }

	j.at("agentID").get_to(v.m_ID);
	if (j.contains("agentTypeID")) { j.at("agentTypeID").get_to(v.m_AgentTypeID); }
	if (j.contains("corporationID")) { j.at("corporationID").get_to(v.m_CorporationID); }
	if (j.contains("divisionID")) { j.at("divisionID").get_to(v.m_DivisionID);  }
	if (j.contains("isLocator")) { j.at("isLocator").get_to(v.m_IsLocator); }
	if (j.contains("level")) { j.at("level").get_to(v.m_Level); }
	if (j.contains("locationID")) { j.at("locationID").get_to(v.m_LocationID); }
}

void EVE::Assets::from_json(const nlohmann::json& j, Constellation& v)
{
	if (!j.contains("constellationID")) { throw std::runtime_error("constellationID is not found."); }
	if (!j.contains("regionID")) { throw std::runtime_error("regionID is not found."); }

	j.at("constellationID").get_to(v.m_ID);
	j.at("regionID").get_to(v.m_RegionID);
	if (j.contains("nameID")) { j.at("nameID").get_to(v.m_NameID); }
	if (j.contains("name")) { j.at("name").get_to(v.m_Name); }
	if (j.contains("radius")) { j.at("radius").get_to(v.m_Radius); }
	if (j.contains("center")) { v.m_Center = j.at("center").get<Point>(); }
	if (j.contains("max")) { v.m_Max = j.at("max").get<Point>(); }
	if (j.contains("min")) { v.m_Min = j.at("min").get<Point>(); }
}

void EVE::Assets::from_json(const nlohmann::json& j, Point& v)
{
	if (j.contains("x")) { j.at("x").get_to(v.m_X); }
	if (j.contains("y")) { j.at("y").get_to(v.m_Y); }
	if (j.contains("z")) { j.at("z").get_to(v.m_Z); }
}

void EVE::Assets::from_json(const nlohmann::json& j, Region& v)
{
	if (!j.contains("regionID")) { throw std::runtime_error("regionID is not found."); }

	j.at("regionID").get_to(v.m_ID);
	if (j.contains("nameID")) { j.at("nameID").get_to(v.m_NameID); }
	if (j.contains("name")) { j.at("name").get_to(v.m_Name); }
	v.m_NameSearch = tolower(v.m_Name);
	if (j.contains("descriptionID")) { j.at("descriptionID").get_to(v.m_DescriptionID); }
	if (j.contains("factionID")) { j.at("factionID").get_to(v.m_FactionID); }
	if (j.contains("nebula")) { j.at("nebula").get_to(v.m_Nebula); }
	if (j.contains("center")) { v.m_Center = j.at("center").get<Point>(); }
	if (j.contains("max")) { v.m_Max = j.at("max").get<Point>(); }
	if (j.contains("min")) { v.m_Min = j.at("min").get<Point>(); }
}

void EVE::Assets::from_json(const nlohmann::json& j, SolarSystem& v)
{
	if (!j.contains("solarSystemID")) { throw std::runtime_error("solarSystemID is not found."); }
	if (!j.contains("constellationID")) { throw std::runtime_error("constellationID is not found."); }
	if (!j.contains("regionID")) { throw std::runtime_error("RegionID is not found."); }

	j.at("solarSystemID").get_to(v.m_ID);
	j.at("constellationID").get_to(v.m_ConstellationID);
	j.at("regionID").get_to(v.m_RegionID);
	if (j.contains("nameID")) { j.at("nameID").get_to(v.m_NameID); }
	if (j.contains("name")) { j.at("name").get_to(v.m_Name); }
	v.m_NameSearch = tolower(v.m_Name);
	if (j.contains("sunTypeID")) { j.at("sunTypeID").get_to(v.m_SunTypeID); }
	if (j.contains("border")) { j.at("border").get_to(v.m_Border); }
	if (j.contains("corridor")) { j.at("corridor").get_to(v.m_Corridor); }
	if (j.contains("fringe")) { j.at("fringe").get_to(v.m_Fringe); }
	if (j.contains("hub")) { j.at("hub").get_to(v.m_Hub); }
	if (j.contains("international")) { j.at("international").get_to(v.m_International); }
	if (j.contains("regional")) { j.at("regional").get_to(v.m_Regional); }
	if (j.contains("luminosity")) { j.at("luminosity").get_to(v.m_Luminosity); }
	if (j.contains("security")) { j.at("security").get_to(v.m_Security); }
	if (j.contains("radius")) { j.at("radius").get_to(v.m_Radius); }
	if (j.contains("securityClass")) { j.at("securityClass").get_to(v.m_SecurityClass); }
	if (j.contains("stations")) { j.at("stations").get_to(v.m_FlagStations); }
	if (j.contains("center")) { v.m_Center = j.at("center").get<Point>(); }
	if (j.contains("max")) { v.m_Max = j.at("max").get<Point>(); }
	if (j.contains("min")) { v.m_Min = j.at("min").get<Point>(); }
}

void EVE::Assets::from_json(const nlohmann::json& j, Station& v)
{
	if (!j.contains("stationID")) { throw std::runtime_error("stationID is not found."); }
	if (!j.contains("solarSystemID")) { throw std::runtime_error("solarSystemID is not found."); }
	if (!j.contains("constellationID")) { throw std::runtime_error("constellationID is not found."); }
	if (!j.contains("regionID")) { throw std::runtime_error("RegionID is not found."); }

	j.at("stationID").get_to(v.m_ID);
	j.at("solarSystemID").get_to(v.m_SolarSystemID);
	j.at("constellationID").get_to(v.m_ConstellationID);
	j.at("regionID").get_to(v.m_RegionID);
	if (j.contains("stationTypeID")) { j.at("stationTypeID").get_to(v.m_StationTypeID); }
	if (j.contains("name")) { j.at("name").get_to(v.m_Name); }
	v.m_NameSearch = tolower(v.m_Name);
	if (j.contains("corporationID")) { j.at("corporationID").get_to(v.m_CorporationID); }
	if (j.contains("dockingCostPerVolume")) { j.at("dockingCostPerVolume").get_to(v.m_DockingCostPerVolume); }
	if (j.contains("maxShipVolumeDockable")) { j.at("maxShipVolumeDockable").get_to(v.m_MaxShipVolumeDockable); }
	if (j.contains("officeRentalCost")) { j.at("officeRentalCost").get_to(v.m_OfficeRentalCost); }
	if (j.contains("operationID")) { j.at("operationID").get_to(v.m_OperationID); }
	if (j.contains("reprocessingEfficiency")) { j.at("reprocessingEfficiency").get_to(v.m_ReprocessingEfficiency); }
	if (j.contains("reprocessingHangarFlag")) { j.at("reprocessingHangarFlag").get_to(v.m_ReprocessingHangarFlag); }
	if (j.contains("reprocessingStationsTake")) { j.at("reprocessingStationsTake").get_to(v.m_ReprocessingStationsTake); }
	if (j.contains("security")) { j.at("security").get_to(v.m_Security); }
	if (j.contains("position")) { v.m_Position = j.at("position").get<Point>(); }
}

void EVE::Assets::from_json(const nlohmann::json& j, Blueprint& v)
{
	if (!j.contains("id")) { throw std::runtime_error("blueprint id is not found."); }

	j.at("id").get_to(v.m_ID);
	if (j.contains("production_limit")) { j.at("production_limit").get_to(v.m_ProductionLimit); }
	if (j.contains("copying_time")) { j.at("copying_time").get_to(v.m_CopyingTime); }
	if (j.contains("reaction")) { j.at("reaction").get_to(v.m_Reaction); }
	if (j.contains("manufacturing_time")) { j.at("manufacturing_time").get_to(v.m_ManufacturingTime); }
	if (j.contains("manufacturing_materials")) { from_json(j["manufacturing_materials"], v.m_ManufacturingMaterials); }
	if (j.contains("manufacturing_products")) { from_json(j["manufacturing_products"], v.m_ManufacturingProducts); }
	if (j.contains("invention_time")) { j.at("invention_time").get_to(v.m_InventionTime); }
	if (j.contains("invention_materials")) { from_json(j["invention_materials"], v.m_InventionMaterials); }
	if (j.contains("invention_products")) { from_json(j["invention_products"], v.m_InventionProducts); }
	if (j.contains("research_me_time")) { j.at("research_me_time").get_to(v.m_ResearchMeTime); }
	if (j.contains("research_me_materials")) { from_json(j["research_me_materials"], v.m_ResearchMeMaterials); }
	if (j.contains("research_pe_time")) { j.at("research_pe_time").get_to(v.m_ResearchPeTime); }
	if (j.contains("research_pe_materials")) { from_json(j["research_pe_materials"], v.m_ResearchPeMaterials); }
	if (j.contains("market_group_id")) { j.at("market_group_id").get_to(v.m_MarketGroupId); }
	//assert(v.m_ManufacturingProducts.size() == 1);
	if (v.m_ManufacturingProducts.size() == 1) { v.m_TypeID = v.m_ManufacturingProducts[0].type_id(); }
}

void EVE::Assets::from_json(const nlohmann::json& j, BlueprintSettings& v)
{
	if (!j.contains("id")) { throw std::runtime_error("blueprint id is not found."); }

	j.at("id").get_to(v.m_ID);

	std::string me;
	if (j.contains("me")) { j.at("me").get_to(me); };
	enumFromString(arrBlueprintME, me, v.m_BpME);

	std::string me_struct;
	if (j.contains("me_struct")) { j.at("me_struct").get_to(me_struct); };
	enumFromString(arrStructureME, me_struct, v.m_StructME);

	std::string me_rig;
	if (j.contains("me_rig")) { j.at("me_rig").get_to(me_rig); };
	enumFromString(arrRigME, me_rig, v.m_RigME);

	if (j.contains("weight")) { j.at("weight").get_to(v.m_Weight); };
	if (j.contains("maximum_runs")) { j.at("maximum_runs").get_to(v.m_MaxRuns); };
}

void EVE::Assets::from_json(const nlohmann::json& j, std::vector<Material>& v)
{
	for (const auto& elem : j)
	{
		std::uint32_t tmp_id{};
		elem.at("id").get_to(tmp_id);

		std::uint64_t tmp_quantity{};
		elem.at("quantity").get_to(tmp_quantity);

		v.emplace_back(tmp_id, tmp_quantity);
	}
}

void EVE::Assets::from_json(const nlohmann::json& j, std::vector<InventionProduct>& v)
{
	for (const auto& elem : j)
	{
		int tmp_id{};
		elem.at("id").get_to(tmp_id);

		std::uint64_t temp_quantity{};
		elem.at("quantity").get_to(temp_quantity);

		float temp_probability{};
		elem.at("probability").get_to(temp_probability);

		v.emplace_back(tmp_id, temp_quantity, temp_probability);
	}
}

void EVE::Assets::from_json(const nlohmann::json& j, Type& v)
{
	if (!j.contains("id")) { throw std::runtime_error("type id is not found."); }

	j.at("id").get_to(v.m_ID);

	if (j.at("name").contains(Setting::LocTag)) 
		j.at("name").at(Setting::LocTag).get_to(v.m_Name);
	else 
		j.at("name").at(Setting::LocTagDefault).get_to(v.m_Name);

	v.m_NameSearch = tolower(v.m_Name);

	if (j.contains("description")) 
	{
		if (j.at("description").contains(Setting::LocTag))
			j.at("description").at(Setting::LocTag).get_to(v.m_Description); 
	}
	if (j.contains("blueprint_ID")) { j.at("blueprint_ID").get_to(v.m_BlueprintID); }
	if (j.contains("icon_ID")) { j.at("icon_ID").get_to(v.m_IconID); }
	if (j.contains("base_price")) { j.at("base_price").get_to(v.m_BasePrice); }
	if (j.contains("mass")) { j.at("mass").get_to(v.m_Mass); }
	if (j.contains("capacity")) { j.at("capacity").get_to(v.m_Capacity); }
	if (j.contains("volume")) { j.at("volume").get_to(v.m_Volume); }
	if (j.contains("packaged_volume")) { j.at("packaged_volume").get_to(v.m_PackagedVolume); }
	if (j.contains("group_ID")) { j.at("group_ID").get_to(v.m_GroupID); }
	if (j.contains("category_ID")) { j.at("category_ID").get_to(v.m_CategoryID); }
	if (j.contains("market_group_ID")) { j.at("market_group_ID").get_to(v.m_MarketGroupID); }
}

void EVE::Assets::from_json(const nlohmann::json& j, MarketGroup& v)
{
	if (!j.contains("id")) { throw std::runtime_error("market group id is not found."); }

	j.at("id").get_to(v.m_ID);
	if (j.contains("parent_id")) { j.at("parent_id").get_to(v.m_ParentID); }
	if (j.contains("name")) { j.at("name").get_to(v.m_Name); }
}

void EVE::Assets::from_json(const nlohmann::json& j, Group& v)
{
	if (!j.contains("id")) { throw std::runtime_error("group id is not found."); }

	j.at("id").get_to(v.m_ID);
	if (j.contains("category_id")) { j.at("category_id").get_to(v.m_CategoryID); }
	if (j.contains("name")) { j.at("name").get_to(v.m_Name); }
}

void EVE::Assets::from_json(const nlohmann::json& j, Category& v)
{
	if (!j.contains("id")) { throw std::runtime_error("category id is not found."); }

	j.at("id").get_to(v.m_ID);
	if (j.contains("name")) { j.at("name").get_to(v.m_Name); }
}

void EVE::Assets::from_json(const nlohmann::json& j, PI& v)
{
	if (!j.contains("id")) { throw std::runtime_error("pi id is not found."); }

	j.at("id").get_to(v.m_ID);
	if (j.contains("schema_ID")) { j.at("schema_ID").get_to(v.m_SchemaID); }
	if (j.contains("cycle_time")) { j.at("cycle_time").get_to(v.m_CycleTime); }
	if (j.contains("quantity")) { j.at("quantity").get_to(v.m_Quantity); }
	if (j.contains("materials")) { from_json(j["materials"], v.m_Materials); }
	if (j.contains("pins")) { j.at("pins").get_to(v.m_Pins); }
}

void EVE::Assets::from_json(const nlohmann::json& j, Order& v)
{
	if (!j.contains("order_id")) { throw std::runtime_error("order id is not found."); }

	j.at("order_id").get_to(v.m_ID);
	if (j.contains("duration")) { j.at("duration").get_to(v.m_Duration); }
	if (j.contains("is_buy_order")) { j.at("is_buy_order").get_to(v.m_IsBuyOrder); }
	if (j.contains("issued")) { j.at("issued").get_to(v.m_Issued); }
	if (j.contains("location_id")) { j.at("location_id").get_to(v.m_LocationID); }
	if (j.contains("min_volume")) { j.at("min_volume").get_to(v.m_MinVolume); }
	if (j.contains("price")) { j.at("price").get_to(v.m_Price); }
	if (j.contains("range")) { j.at("range").get_to(v.m_Range); }
	if (j.contains("system_id")) { j.at("system_id").get_to(v.m_SystemID); }
	if (j.contains("type_id")) { j.at("type_id").get_to(v.m_TypeID); }
	if (j.contains("volume_remain")) { j.at("volume_remain").get_to(v.m_VolumeRemain); }
	if (j.contains("volume_total")) { j.at("volume_total").get_to(v.m_VolumeTotal); }
}

void EVE::Assets::from_json(const nlohmann::json& j, SystemCostIndices& v)
{
	if (!j.contains("solar_system_id")) { throw std::runtime_error("solar system id is not found."); }

	j.at("solar_system_id").get_to(v.m_ID);
	if (j.contains("cost_indices"))
	{
		for (const auto& elem : j.at("cost_indices"))
		{
			double index{};
			if (elem.contains("cost_index")) { elem.at("cost_index").get_to(index); }

			if (elem.contains("activity"))
			{
				const std::string activity = elem.at("activity");
				if (activity == "manufacturing") { v.m_Manufacturing = index; }
				else if (activity == "reaction") { v.m_Reaction = index; }
				else if (activity == "researching_time_efficiency") { v.m_ResearchTimeEfficiency = index; }
				else if (activity == "researching_material_efficiency") { v.m_ResearchMaterialEfficiency = index; }
				else if (activity == "copying") { v.m_Copying = index; }
				else if (activity == "invention") { v.m_Invention = index; }
			}
		}
	}
}

void EVE::Assets::from_json(const nlohmann::json& j, MarketPrice& v)
{
	if (!j.contains("type_id")) { throw std::runtime_error("type id is not found."); }

	j.at("type_id").get_to(v.m_ID);
	if (j.contains("adjusted_price")) { j.at("adjusted_price").get_to(v.m_Adjusted); }
	if (j.contains("average_price")) { j.at("average_price").get_to(v.m_Average); }
}
