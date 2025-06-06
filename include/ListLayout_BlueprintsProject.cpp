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

#include "ListLayout_BlueprintsProject.hpp"
#include "BlueprintProject.hpp"
#include "FormProject.hpp"
#include "EnumTools.hpp"

EVE::Industry::ListLayoutBlueprintsProject::ListLayoutBlueprintsProject()
{
}

void EVE::Industry::ListLayoutBlueprintsProject::createColumns(wxListCtrl* list)
{
	list->AppendColumn("Blueprint");
	list->SetColumnWidth(0, 350);
	list->AppendColumn("Group");
	list->SetColumnWidth(1, 350);
	list->AppendColumn("System");
	list->SetColumnWidth(2, 250);
	list->AppendColumn("System cost index");
	list->SetColumnWidth(3, 120);
	list->AppendColumn("Blueprint ME");
	list->SetColumnWidth(4, 80);
	list->AppendColumn("Struct ME");
	list->SetColumnWidth(5, 80);
	list->AppendColumn("Rig ME");
	list->SetColumnWidth(6, 80);
	list->AppendColumn("Max. runs (one job)");
	list->SetColumnWidth(7, 120);
	list->AppendColumn("Struct bonus (-isk)");
	list->SetColumnWidth(8, 120);
	list->AppendColumn("Facility tax");
	list->SetColumnWidth(9, 100);
}

wxString EVE::Industry::ListLayoutBlueprintsProject::getItemText(int owner_id, void* container, const long index, const long column)
{
	const auto& list = *reinterpret_cast<std::vector<BlueprintProject>*>(container);
	const auto& item = list[index];

	switch (column)
	{
	case 0:
		return item.m_Blueprint.towxString();
	case 1:
		return item.m_Blueprint.group().towxString();
	case 2:
	{
		if (item.m_SolarSystem.id() != 0)
		{
			return item.m_SolarSystem.towxString();
		}

		return std::string();
	}
	case 3:
	{
		if (item.m_SolarSystem.id() != 0)
		{
			return item.m_SolarSystem.costIndexString(item.m_Blueprint.isReaction());
		}

		return std::string();
	}
	case 4:
		return stringFromEnum(EVE::Assets::arrBlueprintME, item.m_ME.m_BpME);
	case 5:
		return stringFromEnum(EVE::Assets::arrStructureME, item.m_ME.m_StructME);
	case 6:
	{
		if (item.m_SolarSystem.id() != 0)
		{
			const bool isReaction = item.m_Blueprint.isReaction();

			return std::format("{} ({:.4f})",
				stringFromEnum(EVE::Assets::arrRigME, item.m_ME.m_RigME),
				EVE::Assets::me(item.m_SolarSystem.security(), isReaction, item.m_ME.m_RigME));
		}

		return std::string("<set 'system'>");
	}
	case 7:
		return std::format(std::locale(""), "{:L}", item.m_MaxRunsPerJob);
	case 8:
		return std::format(std::locale(""), "{:.2f}%", item.m_StructRoleBonus * 100);
	case 9:
		return std::format(std::locale(""), "{:.2f}%", item.m_FacilityTax * 100);
	default:
		return std::string();
	}
}

wxItemAttr* EVE::Industry::ListLayoutBlueprintsProject::getItemColumnAttr(void* container, const long index, const long column)
{
	return nullptr;
}

int EVE::Industry::ListLayoutBlueprintsProject::getItemImage(void* container, const long index, const std::map<std::uint32_t, std::size_t>& vIdsIcons)
{
	const auto& list = *reinterpret_cast<std::vector<BlueprintProject>*>(container);
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

void EVE::Industry::ListLayoutBlueprintsProject::copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns)
{
}

void EVE::Industry::ListLayoutBlueprintsProject::deleteSelectedListItems(void* container, std::vector<long>& lines)
{
}

void EVE::Industry::ListLayoutBlueprintsProject::activateListItem(void* container, const long index, wxWindow* parent)
{
}