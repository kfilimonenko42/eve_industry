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

#include "wxPageBlueprintsProject.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_BlueprintsProject.hpp"
#include "FormProject.hpp"
#include "Assets.hpp"
#include "StringTools.hpp"
#include "FormSelectSolarSystem.hpp"
#include "FormSelectBlueprintME.hpp"
#include "FormSelectStructME.hpp"
#include "FormSelectRigME.hpp"
#include "FormSelectMaxRuns.hpp"

constexpr int ID_STATUS_SETSOLARSYSTEM = 10001;
constexpr int ID_STATUS_SETBLUEPRINTME = 10002;
constexpr int ID_STATUS_SETSTRUCTUREME = 10003;
constexpr int ID_STATUS_SETRIGME = 10004;
constexpr int ID_STATUS_SETMAXRUNS = 10005;

using vListCtrl = wxVirtualListCtrl<EVE::Industry::BlueprintProject>;

EVE::Industry::wxPageBlueprintsProject::wxPageBlueprintsProject(
	wxWindow* parent,
	wxWindow* formProject,
	ListDataWrapper<BlueprintProject>* materials)
	: wxWindow(parent, wxID_ANY), m_Parent{ parent }, m_FormProject{ formProject }, m_Blueprints{ materials }
{
	createControls();
}

void EVE::Industry::wxPageBlueprintsProject::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::wxPageBlueprintsProject::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::wxPageBlueprintsProject::updateImages()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	m_Blueprints->setImages(_list);
}

void EVE::Industry::wxPageBlueprintsProject::createControls()
{
	wxPanel* mainPanel = new wxPanel(m_Parent);

	wxPanel* btnPanelLine1 = new wxPanel(mainPanel);

	wxButton* btnCalculateIndustry = new wxButton(btnPanelLine1, wxID_ANY, "calculate");
	btnCalculateIndustry->Bind(wxEVT_BUTTON, &wxPageBlueprintsProject::OnCalculateProject, this);

	wxBoxSizer* btn_sizer1 = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer1->Add(btnCalculateIndustry, 0, wxLeft | wxBottom | wxTop, 5);
	btnPanelLine1->SetSizer(btn_sizer1);

	m_VirtualList = new vListCtrl(
		mainPanel,
		std::make_unique<ListLayoutBlueprintsProject>(),
		&m_Blueprints->get(),
		wxDefaultPosition,
		wxSize(200, 200));
	m_VirtualList->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &wxPageBlueprintsProject::OnListRightClick, this);

	std::function<void()> updateImageMethod = std::bind(&wxPageBlueprintsProject::updateImages, this);
	m_Blueprints->addUpdater(std::make_unique<ImagesUpdater>(updateImageMethod));

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel_sizer->Add(btnPanelLine1, 0, wxLEFT | wxTOP, 5);
	panel_sizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	mainPanel->SetSizer(panel_sizer);

	wxBoxSizer* page_sizer = new wxBoxSizer(wxVERTICAL);
	page_sizer->Add(mainPanel, 1, wxEXPAND);
	mainPanel->GetParent()->SetSizer(page_sizer);
}

void EVE::Industry::wxPageBlueprintsProject::OnCalculateProject(wxCommandEvent& event)
{
	dynamic_cast<FormProject*>(m_FormProject)->calculateProject();
}

void EVE::Industry::wxPageBlueprintsProject::OnListRightClick(wxListEvent& event)
{
	wxMenu menu;
	menu.Append(ID_STATUS_SETSOLARSYSTEM, "Set 'Solar System'");
	menu.Append(ID_STATUS_SETBLUEPRINTME, "Set 'Blueprint ME'");
	menu.Append(ID_STATUS_SETSTRUCTUREME, "Set 'Structure ME'");
	menu.Append(ID_STATUS_SETRIGME, "Set 'Rig ME'");
	menu.Append(ID_STATUS_SETMAXRUNS, "Set 'Maximum runs'");
	menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &wxPageBlueprintsProject::OnListPopupClick, this);
	PopupMenu(&menu);

	event.Skip();
}

void EVE::Industry::wxPageBlueprintsProject::OnListPopupClick(wxCommandEvent& event)
{
	const std::vector<long> sLines = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	if (sLines.empty())
	{
		return;
	}

	switch (event.GetId())
	{
	case ID_STATUS_SETSOLARSYSTEM:
	{
		std::unique_ptr<FormSelectSolarSystem> dialog = std::make_unique<FormSelectSolarSystem>(m_FormProject);

		if (dialog->ShowModal() == wxID_OK && m_FormProject)
		{
			dynamic_cast<FormProject*>(m_FormProject)->setSolarSystem(dialog->get(), sLines);
		}
		break;
	}
	case ID_STATUS_SETBLUEPRINTME:
	{
		std::unique_ptr<FormSelectBlueprintME> dialog = std::make_unique<FormSelectBlueprintME>(m_FormProject);

		if (dialog->ShowModal() == wxID_OK && m_FormProject)
		{
			const EVE::Assets::BlueprintME result = dialog->get();
			dynamic_cast<FormProject*>(m_FormProject)->setME(result, sLines);
		}
		break;
	}
	case ID_STATUS_SETSTRUCTUREME:
	{
		std::unique_ptr<FormSelectStructME> dialog = std::make_unique<FormSelectStructME>(m_FormProject);

		if (dialog->ShowModal() == wxID_OK && m_FormProject)
		{
			const EVE::Assets::StructureME result = dialog->get();
			dynamic_cast<FormProject*>(m_FormProject)->setME(result, sLines);
		}
		break;
	}
	case ID_STATUS_SETRIGME:
	{
		std::unique_ptr<FormSelectRigME> dialog = std::make_unique<FormSelectRigME>(m_FormProject);

		if (dialog->ShowModal() == wxID_OK && m_FormProject)
		{
			const EVE::Assets::RigME result = dialog->get();
			dynamic_cast<FormProject*>(m_FormProject)->setME(result, sLines);
		}
		break;
	}
	case ID_STATUS_SETMAXRUNS:
	{
		std::unique_ptr<FormSelectMaxRuns> dialog = std::make_unique<FormSelectMaxRuns>(m_FormProject);

		if (dialog->ShowModal() == wxID_OK && m_FormProject)
		{
			const std::uint64_t result = dialog->get();
			dynamic_cast<FormProject*>(m_FormProject)->setMaximumRuns(result, sLines);
		}
		break;
	}
	}
}