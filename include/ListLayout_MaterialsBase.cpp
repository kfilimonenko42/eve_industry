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

#include "ListLayout_MaterialsBase.hpp"
#include "MaterialBase.hpp"
#include "OpenFormType.hpp"

void EVE::Industry::ListLayoutMaterialsBase::createColumns(wxListCtrl* list)
{
	list->AppendColumn("Type");
	list->SetColumnWidth(0, 400);
	list->AppendColumn("Group");
	list->SetColumnWidth(1, 400);
	list->AppendColumn("Quantity");
	list->SetColumnWidth(2, 100);
	list->AppendColumn("Volume (packaged)");
	list->SetColumnWidth(3, 150);
	list->AppendColumn("Price (sell)");
	list->SetColumnWidth(4, 100);
	list->AppendColumn("Price (buy)");
	list->SetColumnWidth(5, 100);
}

wxString EVE::Industry::ListLayoutMaterialsBase::getItemText(int owner_id, void* container, const long index, const long column)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialBase>*>(container);
	const auto& item = list[index];

	switch (column)
	{
	case 0:
		return item.m_Type.towxString();
	case 1:
		return item.m_Type.group().towxString();
	case 2:
		return item.m_Type.quantityToString();
	case 3:
		return item.m_Type.volumeTotalToString();
	case 4:
		return priceSellToString(UpdatePriceRecord{ owner_id, item.id(), item.m_EsiSettings }, item.m_Type.getQuantity());
	case 5:
		return priceBuyToString(UpdatePriceRecord{ owner_id, item.id(), item.m_EsiSettings }, item.m_Type.getQuantity());
	default:
		return "";
	}
}

wxItemAttr* EVE::Industry::ListLayoutMaterialsBase::getItemColumnAttr(void* container, const long index, const long column)
{
	return nullptr;
}

int EVE::Industry::ListLayoutMaterialsBase::getItemImage(void* container, const long index, const std::map<std::uint32_t, std::size_t>& vIdsIcons)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialBase>*>(container);
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

void EVE::Industry::ListLayoutMaterialsBase::copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialBase>*>(container);

	const std::size_t colSize = columns.size();

	wxString data;
	for (const long& line : lines)
	{
		const auto& item = list[line];

		if (!data.empty())
		{
			data += '\n';
		}

		for (std::size_t cIndex = 0; cIndex < colSize; ++cIndex)
		{
			if (cIndex > 0 && cIndex < colSize)
			{
				data += '\t';
			}

			long index = columns[cIndex];
			switch (index)
			{
			case 0:
				data += item.m_Type.wxName();
				break;
			case 1:
				data += item.m_Type.group().wxName();
				break;
			case 2:
				data += std::format("{}", item.m_Type.getQuantity());
				break;
			case 3:
				data += std::format("{:.2f}", item.m_Type.getVolumeTotal());
				break;
			}
		}
	}

	if (!data.empty() && wxTheClipboard->Open())
	{
		wxTheClipboard->AddData(new wxTextDataObject(data));
		wxTheClipboard->Close();
	}
}

void EVE::Industry::ListLayoutMaterialsBase::deleteSelectedListItems(void* container, std::vector<long>& lines)
{
}

void EVE::Industry::ListLayoutMaterialsBase::activateListItem(void* container, const long index, wxWindow* parent)
{
	const auto& list = *reinterpret_cast<std::vector<MaterialBase>*>(container);
	const auto& item = list[index];

	openFormType(item.m_Type, parent);
}