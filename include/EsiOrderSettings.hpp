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

#ifndef _EVEINDUSTRY_ESISETTINGS_HPP_
#define _EVEINDUSTRY_ESISETTINGS_HPP_

#include <cstdint>
#include <chrono>

namespace EVE::Industry
{

    constexpr std::uint32_t REGION_FORGE = 10000002;
    constexpr std::uint32_t SYSTEM_JITA = 30000142;
    constexpr std::uint32_t STATION_JITA44 = 60003760;

    struct EsiOrderSettings
    {
        std::uint32_t m_RegionID{ REGION_FORGE };
        std::uint32_t m_SolarSystemID{ SYSTEM_JITA };
        std::uint32_t m_StationID{ STATION_JITA44 };

        std::uint32_t saveID() const
        {
            if (m_StationID > 0)
            {
                return m_StationID;
            }
            else if (m_SolarSystemID > 0)
            {
                return m_SolarSystemID;
            }

            return m_RegionID;
        }
    };

} // EVE::Industry

#endif // _EVEINDUSTRY_ESISETTINGS_HPP_