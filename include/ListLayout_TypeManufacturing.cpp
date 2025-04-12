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

#include "ListLayout_TypeManufacturing.hpp"
#include "TypeManufacturing.hpp"

void EVE::Industry::ListLayoutTypeManufacturing::createColumns(wxListCtrl* list)
{
	list->AppendColumn("Name");
	list->SetColumnWidth(0, 450);
	list->AppendColumn("Quantity");
	list->SetColumnWidth(1, 100);
}

wxString EVE::Industry::ListLayoutTypeManufacturing::getItemText(int owner_id, void* container, const long index, const long column)
{
	const auto& list = *reinterpret_cast<std::vector<TypeManufacturing>*>(container);
	const auto& item = list[index];

	switch (column)
	{
	case 0:
		return item.m_Type.wxName();
	case 1:
		return item.m_Type.quantityToString();
	default:
		return "";
	}
}

wxItemAttr* EVE::Industry::ListLayoutTypeManufacturing::getItemColumnAttr(void* container, const long index, const long column)
{
	return nullptr;
}

int EVE::Industry::ListLayoutTypeManufacturing::getItemImage(void* container, const long index, const std::map<std::uint32_t, std::size_t>& vIdsIcons)
{
	const auto& list = *reinterpret_cast<std::vector<TypeManufacturing>*>(container);
	const auto& item = list[index];

	const std::uint32_t type_id = item.id();
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

void EVE::Industry::ListLayoutTypeManufacturing::copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns)
{
}

void EVE::Industry::ListLayoutTypeManufacturing::deleteSelectedListItems(void* container, std::vector<long>& lines)
{
}

void EVE::Industry::ListLayoutTypeManufacturing::activateListItem(void* container, const long index, wxWindow* parent)
{
}