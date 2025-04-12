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

#ifndef _EVEAPPSETTINGS_DEFAULTSETTINGS_HPP_
#define _EVEAPPSETTINGS_DEFAULTSETTINGS_HPP_

#include <string>
#include <utility>
#include <array>
#include <filesystem>

namespace EVE::APPSETTINGS
{

    namespace Paths
    {
        static const std::string Agents{ "/assets/agents.json" };
        static const std::string Constellations{ "/assets/constellations.json" };
        static const std::string Regions{ "/assets/regions.json" };
        static const std::string SolarSystems{ "/assets/solarsystems.json" };
        static const std::string Stations{ "/assets/stations.json" };
        static const std::string Blueprints{ "/assets/bps.json" };
        static const std::string BlueprintsSettings{ "/assets/bps_settings.json" };
        static const std::string BlueprintsSettings_Users{ "/user/bps_settings.json" };
        static const std::string Types{ "/assets/types.json" };
        static const std::string MarketGroups{ "/assets/market_groups.json" };
        static const std::string Groups{ "/assets/groups.json" };
        static const std::string Categories{ "/assets/categories.json" };
        static const std::string PISchemas{ "/assets/pis.json" };
    }

    static const std::pair<std::string, std::string> LocalizationList[] = {
        {"de", "German"},
        {"en", "English"},
        {"es", "Spanish"},
        {"fre", "French"},
        {"it", "Italian"},
        {"ja", "Japanese"},
        {"ko", "Korean"},
        {"ru", "Russian"},
        {"zh", "Chinese"}
    };

    namespace Default
    {
        static const std::string LocTag{ "en" };
    }

    [[nodiscard]] inline bool userBpSettingsExists()
    {
        return std::filesystem::exists(std::filesystem::current_path().string() + Paths::BlueprintsSettings_Users);
    }

} // EVE::APPSETTINGS

#endif // _EVEAPPSETTINGS_DEFAULTSETTINGS_HPP_