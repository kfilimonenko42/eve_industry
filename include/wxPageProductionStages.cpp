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

constexpr int ID_GET_MATERIALS = 10001;
constexpr int ID_STATUS_OUTSTANDING = 10002;
constexpr int ID_STATUS_INPROGRESS = 10003;
constexpr int ID_STATUS_FINISHED = 10004;
constexpr int ID_BPSETTING_SETMAXRUNS = 10005;

using vListCtrl = wxVirtualListCtrl<EVE::Industry::ProductionStage>;

EVE::Industry::wxPageProductionStages::wxPageProductionStages(
	wxWindow* parent,
	wxWindow* formProject,
	ListDataWrapper<ProductionStage>* stages)
	: wxWindow(parent, wxID_ANY), m_Parent{ parent }, m_FormProject{ formProject }, m_ProductionStages{ stages }
{
	createControls();

	m_UpdTimer.Bind(wxEVT_TIMER, &wxPageProductionStages::OnUpdateTimer, this, m_UpdTimer.GetId());
	m_UpdTimer.Start(1000);
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

void EVE::Industry::wxPageProductionStages::updateTotalLabels()
{
	const std::size_t size = m_ProductionStages->size();
	m_TotalStatuses->SetLabelText(std::format("Total: {}", size));

	const std::size_t countOutstanding = totalStatuses(m_ProductionStages->get(), StageStatus::Outstanding);
	m_OutstandingStatuses->SetLabelText(std::format("Outstanding: {}", countOutstanding));

	const std::size_t countInProgress = totalStatuses(m_ProductionStages->get(), StageStatus::InProgress);
	m_InProgressStatuses->SetLabelText(std::format("In Progress: {}", countInProgress));

	const std::size_t countFinished = totalStatuses(m_ProductionStages->get(), StageStatus::Finished);
	m_FinishedStatuses->SetLabelText(std::format("Finished: {}", countFinished));

	m_TotalJobCost->SetLabelText(std::format(std::locale(""), "Total jobs cost: {:.2Lf}", 
		totalJobsCost(m_ProductionStages->get(), dynamic_cast<FormProject*>(m_FormProject)->projectPtr())));
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
		std::make_unique<ListLayoutProductionStages>(dynamic_cast<FormProject*>(m_FormProject)->projectPtr()),
		m_ProductionStages,
		wxDefaultPosition,
		wxSize(200, 200));
	m_VirtualList->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &wxPageProductionStages::OnListRightClick, this);
	dynamic_cast<vListCtrl*>(m_VirtualList)->setIsImages(true);

	wxPanel* _panelResults = new wxPanel(mainPanel);

	wxFont font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	m_TotalStatuses = new wxStaticText(_panelResults, wxID_ANY, "Total: -");
	m_TotalStatuses->SetFont(font);
	m_OutstandingStatuses = new wxStaticText(_panelResults, wxID_ANY, "Outstanding: -");
	m_OutstandingStatuses->SetFont(font);
	m_OutstandingStatuses->SetForegroundColour(wxColour(214, 147, 101));
	m_InProgressStatuses = new wxStaticText(_panelResults, wxID_ANY, "In Progress: -");
	m_InProgressStatuses->SetFont(font);
	m_InProgressStatuses->SetForegroundColour(wxColour(98, 192, 249));
	m_FinishedStatuses = new wxStaticText(_panelResults, wxID_ANY, "Finished: -");
	m_FinishedStatuses->SetFont(font);
	m_FinishedStatuses->SetForegroundColour(wxColour(70, 150, 81));
	m_TotalJobCost = new wxStaticText(_panelResults, wxID_ANY, "Total jobs cost: -");
	m_TotalJobCost->SetFont(font);

	wxBoxSizer* _resultSizer = new wxBoxSizer(wxVERTICAL);
	_resultSizer->AddSpacer(5);
	_resultSizer->Add(m_TotalStatuses, 0, wxEXPAND);
	_resultSizer->Add(m_OutstandingStatuses, 0, wxEXPAND);
	_resultSizer->Add(m_InProgressStatuses, 0, wxEXPAND);
	_resultSizer->Add(m_FinishedStatuses, 0, wxEXPAND);
	_resultSizer->AddSpacer(5);
	_resultSizer->Add(m_TotalJobCost, 0, wxEXPAND);
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

	if (dynamic_cast<vListCtrl*>(m_VirtualList)->countSelected() == 1)
	{
		menu.AppendSeparator();
		menu.Append(ID_BPSETTING_SETMAXRUNS, "Set 'Maximum runs'");
	}

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
	case ID_BPSETTING_SETMAXRUNS:
	{
		std::unique_ptr<FormSelectInt> dialog = std::make_unique<FormSelectInt>(m_FormProject, "Maximum runs", "Maximum runs per one job", 1, INT_MAX);

		if (dialog->ShowModal() == wxID_OK && m_FormProject)
		{
			const std::uint64_t result = dialog->get();
			auto tmpfp = dynamic_cast<FormProject*>(m_FormProject);
			tmpfp->setMaximumRunsFromStages(result, sLines);
			tmpfp->calculateProject();
		}
		break;
	}
	}
}

void EVE::Industry::wxPageProductionStages::OnUpdateTimer(wxTimerEvent& event)
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->OnUpdateTimer(event);

	event.Skip();
}
