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

#include "ListOfTypes.hpp"

EVE::Industry::Types::Types(
    bool indyTypes,
    bool sort)
    : m_IndyTypes{ indyTypes }, m_Sort{ sort }
{
}

void EVE::Industry::Types::operator()(std::vector<TypeRecord>& result)
{
    result.clear();

    const Assets& assets = Assets::Instance();
    std::for_each(assets.m_TypesContainer.cbegin(), assets.m_TypesContainer.cend(),
        [indyTypes = m_IndyTypes, &result](const EVE::Assets::Type& type)
        {
            const bool add = indyTypes ? (type.m_BlueprintID > 0) : true;
            if (add)
            {
                result.emplace_back(&type);
            }
        });

    if (m_Sort)
    {
        std::sort(std::begin(result), std::end(result), BaseRecordSortByName());
    }
}

EVE::Industry::FilterLeftTypes::FilterLeftTypes(
    bool indyTypes,
    bool sort)
    : m_IndyTypes{ indyTypes }, m_Sort{ sort }
{
}

void EVE::Industry::FilterLeftTypes::operator()(std::vector<TypeRecord>& result, const std::string& txtFilter)
{
    result.clear();

    const Assets& assets = Assets::Instance();
    if (txtFilter.empty())
    {
        Types loadTypes{ m_IndyTypes, m_Sort };
        loadTypes(result);
        return;
    }

    auto filter = std::views::filter(
        [indyTypes = m_IndyTypes, &txtFilter](const EVE::Assets::Type& type)
        {
            return ((indyTypes ? (type.m_BlueprintID > 0) : true) 
                && (type.m_NameSearch.rfind(txtFilter, 0) == 0));
        });

    auto filteredList = assets.m_TypesContainer.get_container() | filter;

    if (filteredList.empty())
    {
        return;
    }

    std::for_each(filteredList.begin(), filteredList.end(),
        [&result](const EVE::Assets::Type& type)
        {
            result.emplace_back(&type);
        });

    if (m_Sort)
    {
        std::sort(std::begin(result), std::end(result), BaseRecordSortByName());
    }
}

