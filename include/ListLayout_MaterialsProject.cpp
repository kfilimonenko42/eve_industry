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

#include "ListLayout_MaterialsProject.hpp"
#include "MaterialProject.hpp"
#include "OpenFormType.hpp"

void EVE::Industry::ListLayoutMaterialsProject::createColumns(wxListCtrl* list)
{
	list->AppendColumn("Type");
	list->SetColumnWidth(0, 400);
	list->AppendColumn("Group");
	list->SetColumnWidth(1, 400);
	list->AppendColumn("Quantity");
	list->SetColumnWidth(2, 100);
	list->AppendColumn("Price (sell)");
	list->SetColumnWidth(3, 100);
	list->AppendColumn("Price (buy)");
	list->SetColumnWidth(4, 100);
}

std::string EVE::Industry::ListLayoutMaterialsProject::getItemText(void* container, const long index, const long column)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialProject>*>(container);
	const auto& item = list[index];

	switch (column)
	{
	case 0:
		return item.m_Type.toString();
	case 1:
		return item.m_Type.group().toString();
	case 2:
		return item.m_Type.quantityToString();
	case 3:
		return item.m_Type.priceSellTotalToString();
	case 4:
		return item.m_Type.priceBuyTotalToString();
	default:
		return "";
	}
}

int EVE::Industry::ListLayoutMaterialsProject::getItemImage(void* container, const long index, const std::map<std::uint32_t, std::size_t>& vIdsIcons)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialProject>*>(container);
	const auto& item = list[index];

	const std::uint32_t type_id = item.m_Type.id();
	if (vIdsIcons.contains(type_id))
	{
		const std::size_t _iconIndex = vIdsIcons.at(type_id);
		if (vIdsIcons.contains(type_id))
		{
			return vIdsIcons.at(type_id);
		}
	}

	return -1;
}

void EVE::Industry::ListLayoutMaterialsProject::copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns)
{
}

void EVE::Industry::ListLayoutMaterialsProject::deleteSelectedListItems(void* container, std::vector<long>& lines)
{
	if (lines.empty())
	{
		return;
	}

	std::reverse(std::begin(lines), std::end(lines));

	auto& list = *reinterpret_cast<std::vector<MaterialProject>*>(container);
	for (const long& i : lines)
	{
		list.erase(std::next(std::begin(list), i));
	}
}

void EVE::Industry::ListLayoutMaterialsProject::activateListItem(void* container, const long index, wxWindow* parent)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialProject>*>(container);
	const auto& item = list[index];

	openFormType(item.m_Type, parent);
}