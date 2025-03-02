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

#ifndef _EVEASSETSPATHS_SETTING_HPP_
#define _EVEASSETSPATHS_SETTING_HPP_

#include <string>

namespace EVE::Assets::Setting
{

	namespace Paths
	{
		static const std::string Agents = "/assets/agents.json";
		static const std::string Constellations = "/assets/constellations.json";
		static const std::string Regions = "/assets/regions.json";
		static const std::string SolarSystems = "/assets/solarsystems.json";
		static const std::string Stations = "/assets/stations.json";
		static const std::string Blueprints = "/assets/bps.json";
		static const std::string BlueprintsSettings = "/assets/bps_settings.json";
		static const std::string Types = "/assets/types.json";
		static const std::string MarketGroups = "/assets/market_groups.json";
		static const std::string Groups = "/assets/groups.json";
		static const std::string Categories = "/assets/categories.json";
		static const std::string PISchemas = "/assets/pis.json";
		static const std::string Orders = "/assets/tmp_order.json";
	}

	static const std::string LocTagDefault = "en";
	static std::string LocTag = "en";

}

#endif // _EVEASSETSPATHS_SETTING_HPP_