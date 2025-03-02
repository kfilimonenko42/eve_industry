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

#include "ListOfStations.hpp"

EVE::Industry::Stations::Stations(
    const std::uint32_t regionID,
    const std::uint32_t solSystemID,
    bool sort)
    : m_RegionID{ regionID }, m_SolarSystemID{ solSystemID }, m_Sort {sort}
{
}

void EVE::Industry::Stations::operator()(std::vector<StationRecord>& result)
{
    result.clear();

    const Assets& assets = Assets::Instance();
    std::for_each(assets.m_StationsContainer.cbegin(), assets.m_StationsContainer.cend(),
        [regionID = m_RegionID, solSystemID = m_SolarSystemID, &result](const EVE::Assets::Station& station)
        {
            const bool add = ((regionID > 0 ? station.m_RegionID == regionID : true)
                && (solSystemID > 0 ? station.m_SolarSystemID == solSystemID : true));
            if (add)
            {
                result.emplace_back(&station);
            }
        });

    if (m_Sort)
    {
        std::sort(std::begin(result), std::end(result), BaseRecordSortByName());
    }
}

EVE::Industry::FilterLeftStations::FilterLeftStations(
    const std::uint32_t regionID,
    const std::uint32_t solSystemID,
    bool sort)
    : m_RegionID{ regionID }, m_SolarSystemID{ solSystemID }, m_Sort{ sort }
{
}

void EVE::Industry::FilterLeftStations::operator()(std::vector<StationRecord>& result, const std::string& txtFilter)
{
    result.clear();

    const Assets& assets = Assets::Instance();
    if (txtFilter.empty())
    {
        Stations loadStations{ m_RegionID, m_SolarSystemID, m_Sort };
        loadStations(result);
        return;
    }

    auto filter = std::views::filter(
        [regionID = m_RegionID, solSystem = m_SolarSystemID, &txtFilter](const EVE::Assets::Station& station)
        {
            return ((regionID > 0 ? station.m_RegionID == regionID : true)
                && (solSystem > 0 ? station.m_SolarSystemID == solSystem : true)
                && station.m_NameSearch.rfind(txtFilter, 0) == 0);
        });

    auto filteredList = assets.m_StationsContainer.get_container() | filter;

    if (filteredList.empty())
    {
        return;
    }

    std::for_each(filteredList.begin(), filteredList.end(),
        [&result](const EVE::Assets::Station& station)
        {
            result.emplace_back(&station);
        });

    if (m_Sort)
    {
        std::sort(std::begin(result), std::end(result), BaseRecordSortByName());
    }
}

