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

#include "wxPageProductionStages.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_ProductionStages.hpp"
#include "FormProject.hpp"
#include "TotalValues.hpp"

constexpr int ID_GET_MATERIALS = 10001;
constexpr int ID_STATUS_OUTSTANDING = 10002;
constexpr int ID_STATUS_INPROGRESS = 10003;
constexpr int ID_STATUS_FINISHED = 10004;

using vListCtrl = wxVirtualListCtrl<EVE::Industry::ProductionStage>;

EVE::Industry::wxPageProductionStages::wxPageProductionStages(
	wxWindow* parent,
	wxWindow* formProject,
	ListDataWrapper<ProductionStage>* stages)
	: wxWindow(parent, wxID_ANY), m_Parent{ parent }, m_FormProject{ formProject }, m_ProductionStages{ stages }
{
	createControls();
}

void EVE::Industry::wxPageProductionStages::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
	updateTotalLabels();
}

void EVE::Industry::wxPageProductionStages::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::wxPageProductionStages::updateImages()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	m_ProductionStages->setImages(_list);
}

void EVE::Industry::wxPageProductionStages::updateTotalLabels()
{
	const std::size_t size = m_ProductionStages->size();
	const std::size_t countOutstanding = totalStatuses(m_ProductionStages->get(), StageStatus::Outstanding);
	const std::size_t countInProgress = totalStatuses(m_ProductionStages->get(), StageStatus::InProgress);
	const std::size_t countFinished = totalStatuses(m_ProductionStages->get(), StageStatus::Finished);
	m_TotalStatuses->SetLabelText(std::format("Total: {}\nOutstanding: {}\nIn Progress: {}\nFinished: {}",
		size, countOutstanding, countInProgress, countFinished));
}

void EVE::Industry::wxPageProductionStages::createControls()
{
	wxPanel* mainPanel = new wxPanel(m_Parent);

	wxPanel* _btnPanel1 = new wxPanel(mainPanel);

	wxButton* btnCopyName = new wxButton(_btnPanel1, wxID_ANY, "copy name");
	btnCopyName->Bind(wxEVT_BUTTON, &wxPageProductionStages::OnCopyName, this);

	wxButton* btnCopyRuns = new wxButton(_btnPanel1, wxID_ANY, "copy runs");
	btnCopyRuns->Bind(wxEVT_BUTTON, &wxPageProductionStages::OnCopyRuns, this);

	wxBoxSizer* _btnPanel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	_btnPanel1Sizer->Add(btnCopyName, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1Sizer->Add(btnCopyRuns, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1->SetSizer(_btnPanel1Sizer);

	m_VirtualList = new vListCtrl(
		mainPanel,
		std::make_unique<ListLayoutProductionStages>(),
		&m_ProductionStages->get(),
		wxDefaultPosition,
		wxSize(200, 200));
	m_VirtualList->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &wxPageProductionStages::OnListRightClick, this);

	std::function<void()> updateImageMethod = std::bind(&wxPageProductionStages::updateImages, this);
	m_ProductionStages->addUpdater(std::make_unique<ImagesUpdater>(updateImageMethod));

	wxPanel* _panelResults = new wxPanel(mainPanel);

	wxFont font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	m_TotalStatuses = new wxStaticText(_panelResults, wxID_ANY, "Total:\nOutstanding:\nIn Progress:\nFinished:");
	m_TotalStatuses->SetFont(font);

	wxBoxSizer* _resultSizer = new wxBoxSizer(wxVERTICAL);
	_resultSizer->AddSpacer(5);
	_resultSizer->Add(m_TotalStatuses, 0, wxEXPAND);
	_resultSizer->AddSpacer(5);
	_panelResults->SetSizer(_resultSizer);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel_sizer->Add(_btnPanel1, 0, wxLEFT | wxTOP, 5);
	panel_sizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	panel_sizer->Add(_panelResults, 0, wxEXPAND | wxLEFT | wxBottom | wxRight, 5);
	mainPanel->SetSizer(panel_sizer);

	wxBoxSizer* page_sizer = new wxBoxSizer(wxVERTICAL);
	page_sizer->Add(mainPanel, 1, wxEXPAND);
	mainPanel->GetParent()->SetSizer(page_sizer);
}

void EVE::Industry::wxPageProductionStages::OnCopyName(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 0 });
}

void EVE::Industry::wxPageProductionStages::OnCopyRuns(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 1 });
}

void EVE::Industry::wxPageProductionStages::OnListRightClick(wxListEvent& event)
{
	wxMenu menu;
	menu.Append(ID_GET_MATERIALS, "Materials");
	menu.AppendSeparator();
	menu.Append(ID_STATUS_OUTSTANDING, "Status 'Outstanding'");
	menu.Append(ID_STATUS_INPROGRESS, "Status 'In Progress'");
	menu.Append(ID_STATUS_FINISHED, "Status 'Finished'");
	menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &wxPageProductionStages::OnListPopupClick, this);
	PopupMenu(&menu);

	event.Skip();
}

void EVE::Industry::wxPageProductionStages::OnListPopupClick(wxCommandEvent& event)
{
	const std::vector<long> sLines = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	if (sLines.empty())
	{
		return;
	}

	switch (event.GetId())
	{
	case ID_GET_MATERIALS:
		dynamic_cast<FormProject*>(m_FormProject)->showMaterialsStages(sLines);
		break;
	case ID_STATUS_OUTSTANDING:
		dynamic_cast<FormProject*>(m_FormProject)->setStageStatus(StageStatus::Outstanding, sLines);
		updateTotalLabels();
		break;
	case ID_STATUS_INPROGRESS:
		dynamic_cast<FormProject*>(m_FormProject)->setStageStatus(StageStatus::InProgress, sLines);
		updateTotalLabels();
		break;
	case ID_STATUS_FINISHED:
		dynamic_cast<FormProject*>(m_FormProject)->setStageStatus(StageStatus::Finished, sLines);
		updateTotalLabels();
		break;
	}
}