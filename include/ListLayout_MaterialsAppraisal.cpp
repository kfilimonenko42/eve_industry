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

#include "ListLayout_MaterialsAppraisal.hpp"
#include "MaterialAppraisal.hpp"
#include "AppraisalContainer.hpp"

void EVE::Industry::ListLayoutMaterialsAppraisal::createColumns(wxListCtrl* list)
{
	list->AppendColumn("Name");
	list->SetColumnWidth(0, 450);
	list->AppendColumn("Sell x1");
	list->SetColumnWidth(1, 100);
	list->AppendColumn("Buy x1");
	list->SetColumnWidth(2, 100);
	list->AppendColumn("Sell all");
	list->SetColumnWidth(3, 100);
	list->AppendColumn("Buy all");
	list->SetColumnWidth(4, 100);
}

std::string EVE::Industry::ListLayoutMaterialsAppraisal::getItemText(int owner_id, void* container, const long index, const long column)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialAppraisal>*>(container);
	const auto& item = list[index];

	switch (column)
	{
	case 0:
		return item.m_Type.toString();
	case 1:
		return priceSellToString(UpdatePriceRecord{ owner_id, item.id(), item.m_EsiSettings });
	case 2:
		return priceBuyToString(UpdatePriceRecord{ owner_id, item.id(), item.m_EsiSettings });
	case 3:
		return priceSellToString(UpdatePriceRecord{ owner_id, item.id(), item.m_EsiSettings }, item.m_Type.getQuantity());
	case 4:
		return priceBuyToString(UpdatePriceRecord{ owner_id, item.id(), item.m_EsiSettings }, item.m_Type.getQuantity());
	default:
		return "";
	}
}

int EVE::Industry::ListLayoutMaterialsAppraisal::getItemImage(void* container, const long index, const std::map<std::uint32_t, std::size_t>& vIdsIcons)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialAppraisal>*>(container);
	const auto& item = list[index];

	const std::uint32_t type_id = item.id();
	if (vIdsIcons.contains(type_id))
	{
		return vIdsIcons.at(type_id);
	}

	return -1;
}

void EVE::Industry::ListLayoutMaterialsAppraisal::copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns)
{
}

void EVE::Industry::ListLayoutMaterialsAppraisal::deleteSelectedListItems(void* container, std::vector<long>& lines)
{
}

void EVE::Industry::ListLayoutMaterialsAppraisal::activateListItem(void* container, const long index, wxWindow* parent)
{
}