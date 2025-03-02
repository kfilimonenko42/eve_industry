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

#include "ListBoxLayoutBox_Station.hpp"
#include "StationRecord.hpp"
#include "FormSelectStation.hpp"

EVE::Industry::ListLayoutBoxStationRecord::ListLayoutBoxStationRecord(wxWindow* mainForm)
	: m_MainForm{ mainForm }
{
}

void EVE::Industry::ListLayoutBoxStationRecord::createColumns(wxListCtrl* list)
{
	list->AppendColumn("name");
	list->SetColumnWidth(0, 350);
}

std::string EVE::Industry::ListLayoutBoxStationRecord::getItemText(void* container, const long index, const long column)
{
	const auto& list = *reinterpret_cast<std::vector<StationRecord>*>(container);
	const auto& item = list[index];

	switch (column)
	{
	case 0:
		return item.toString();
	default:
		return "";
	}
}

int EVE::Industry::ListLayoutBoxStationRecord::getItemImage(void* container, const long index, const std::map<std::uint32_t, std::size_t>& vIdsIcons)
{
	return -1;
}

void EVE::Industry::ListLayoutBoxStationRecord::copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns)
{
}

void EVE::Industry::ListLayoutBoxStationRecord::deleteSelectedListItems(void* container, std::vector<long>& lines)
{
}

void EVE::Industry::ListLayoutBoxStationRecord::activateListItem(void* container, const long index, wxWindow* parent)
{
	if (m_MainForm)
	{
		dynamic_cast<FormSelectStation*>(m_MainForm)->select();
	}
}