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

#include "ListOfRegions.hpp"

EVE::Industry::Regions::Regions(bool sort)
    : m_Sort{ sort }
{
}

void EVE::Industry::Regions::operator()(std::vector<BaseRecord>& result)
{
    result.clear();

    const Assets& assets = Assets::Instance();
    std::for_each(assets.m_RegionsContainer.cbegin(), assets.m_RegionsContainer.cend(),
        [&result](const EVE::Assets::Region& region)
        {
            result.emplace_back(region.m_Name, region.m_ID);
        });

    if (m_Sort)
    {
        std::sort(std::begin(result), std::end(result), BaseRecordSortByName());
    }
}

EVE::Industry::FilterRegions::FilterRegions(bool sort)
    : m_Sort{ sort }
{
}

void EVE::Industry::FilterRegions::operator()(std::vector<BaseRecord>& result, const std::string& txtFilter)
{
    result.clear();

    const Assets& assets = Assets::Instance();
    if (txtFilter.empty())
    {
        Regions loarRegions{ m_Sort };
        loarRegions(result);
        return;
    }

    auto filter = std::views::filter(
        [&txtFilter](const EVE::Assets::Region& region)
        {
            return (region.m_NameSearch.find(txtFilter, 0) != std::string::npos);
        });

    auto filteredList = assets.m_RegionsContainer.get_container() | filter;

    if (filteredList.empty())
    {
        return;
    }

    std::for_each(filteredList.begin(), filteredList.end(),
        [&result](const EVE::Assets::Region& region)
        {
            result.emplace_back(region.m_Name, region.m_ID);
        });

    if (m_Sort)
    {
        std::sort(std::begin(result), std::end(result), BaseRecordSortByName());
    }
}

