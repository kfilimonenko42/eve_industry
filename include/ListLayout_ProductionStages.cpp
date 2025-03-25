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

#include "ListLayout_ProductionStages.hpp"
#include "ProductionStage.hpp"
#include "EnumTools.hpp"
#include "TotalValues.hpp"

void EVE::Industry::ListLayoutProductionStages::createColumns(wxListCtrl* list)
{
	list->AppendColumn("Blueprint");
	list->SetColumnWidth(0, 400);
	list->AppendColumn("Runs");
	list->SetColumnWidth(1, 100);
	list->AppendColumn("Quantity");
	list->SetColumnWidth(2, 100);
	list->AppendColumn("Status");
	list->SetColumnWidth(3, 100);
	list->AppendColumn("Total job cost");
	list->SetColumnWidth(4, 100);
}

wxString EVE::Industry::ListLayoutProductionStages::getItemText(int owner_id, void* container, const long index, const long column)
{
	const auto& list = *reinterpret_cast<std::vector<ProductionStage>*>(container);
	const auto& item = list[index];

	switch (column)
	{
	case 0:
		return item.m_Blueprint.towxString();
	case 1:
		return std::format(std::locale(""), "{:L}", item.m_Runs);
	case 2:
		return std::format(std::locale(""), "{:L}", item.m_Quantity);
	case 3:
		return stringFromEnum(arrStageStatus, item.m_Status);
	case 4:
		return std::format(std::locale(""), "{:.2Lf}", jobCost(item.m_Blueprint, item.m_SolarSystem, item.m_Runs));
	default:
		return "";
	}
}

int EVE::Industry::ListLayoutProductionStages::getItemImage(void* container, const long index, const std::map<std::uint32_t, std::size_t>& vIdsIcons)
{
	const auto& list = *reinterpret_cast<std::vector<ProductionStage>*>(container);
	const auto& item = list[index];

	const std::uint32_t bp_id = item.id();
	if (vIdsIcons.contains(bp_id))
	{
		const std::size_t _iconIndex = vIdsIcons.at(bp_id);
		if (vIdsIcons.contains(bp_id))
		{
			return vIdsIcons.at(bp_id);
		}
	}

	return -1;
}

void EVE::Industry::ListLayoutProductionStages::copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns)
{
	const auto& list = *reinterpret_cast<std::vector<ProductionStage>*>(container);

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
				data += item.m_Blueprint.wxName();
				break;
			case 1:
				data += std::format("{}", item.m_Runs);;
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

void EVE::Industry::ListLayoutProductionStages::deleteSelectedListItems(void* container, std::vector<long>& lines)
{
}

void EVE::Industry::ListLayoutProductionStages::activateListItem(void* container, const long index, wxWindow* parent)
{
}