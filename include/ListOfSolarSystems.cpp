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

#include "ListOfSolarSystems.hpp"

EVE::Industry::SolarSystems::SolarSystems(const std::uint32_t regionID, bool sort)
    : m_RegionID{ regionID }, m_Sort{ sort }
{
}

void EVE::Industry::SolarSystems::operator()(std::vector<SolarSystemRecord>& result)
{
    result.clear();

    const Assets& assets = Assets::Instance();
    std::for_each(assets.m_SolarSystemsContainer.cbegin(), assets.m_SolarSystemsContainer.cend(),
        [regionID = m_RegionID, &result](const EVE::Assets::SolarSystem& solSystem)
        {
            const bool add = (regionID > 0 ? solSystem.m_RegionID == regionID : true);
            if (add)
            {
                result.emplace_back(&solSystem);
            }
        });

    if (m_Sort)
    {
        std::sort(std::begin(result), std::end(result), BaseRecordSortByName());
    }
}

EVE::Industry::FilterLeftSolarSystems::FilterLeftSolarSystems(const std::uint32_t regionID, bool sort)
    : m_RegionID{ regionID }, m_Sort{ sort }
{
}

void EVE::Industry::FilterLeftSolarSystems::operator()(std::vector<SolarSystemRecord>& result, const std::string& txtFilter)
{
	result.clear();

    const Assets& assets = Assets::Instance();
	if (txtFilter.empty())
	{
        SolarSystems loadSolSys{ m_RegionID, m_Sort };
        loadSolSys(result);
		return;
	}

	auto filter = std::views::filter(
		[regionID = m_RegionID, &txtFilter](const EVE::Assets::SolarSystem& solSystem)
		{
			return ((regionID > 0 ? solSystem.m_RegionID == regionID : true) 
                && (solSystem.m_NameSearch.rfind(txtFilter, 0) == 0));
		});

	auto filteredList = assets.m_SolarSystemsContainer.get_container() | filter;

	if (filteredList.empty())
	{
		return;
	}

    std::for_each(filteredList.begin(), filteredList.end(),
        [&result](const EVE::Assets::SolarSystem& solSystem)
        {
            result.emplace_back(&solSystem);
        });

    if (m_Sort)
    {
        std::sort(std::begin(result), std::end(result), BaseRecordSortByName());
    }
}

