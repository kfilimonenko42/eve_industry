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

#ifndef _EVEINDUSTRY_LISTOFSOLARSYSTEMS_HPP_
#define _EVEINDUSTRY_LISTOFSOLARSYSTEMS_HPP_

#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <functional>

#include "Assets.hpp"
#include "SolarSystem.hpp"
#include "SolarSystemRecord.hpp"

namespace EVE::Industry
{

    struct SolarSystems
    {
        explicit SolarSystems(const std::uint32_t regionID = 0, bool sort = false);

        void operator()(std::vector<SolarSystemRecord>& result);

    private:
        std::uint32_t m_RegionID{};
        bool m_Sort{};
    };

    struct FilterLeftSolarSystems
    {
        explicit FilterLeftSolarSystems(const std::uint32_t regionID = 0, bool sort = false);

        void operator()(std::vector<SolarSystemRecord>& result, const std::string& txtFilter);

    private:
        std::uint32_t m_RegionID{};
        bool m_Sort{};
    };

} // EVE::Industry

#endif // _EVEINDUSTRY_LISTOFSOLARSYSTEMS_HPP_