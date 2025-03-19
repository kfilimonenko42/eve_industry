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

#include "FormMaterialsStages.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::MaterialProject>;

EVE::Industry::FormMaterialsStages::FormMaterialsStages(std::vector<MaterialProject>&& materials)
	: wxDialog(nullptr, wxID_ANY, "materials for stages", wxDefaultPosition, wxSize(1024, 800))
{
	createControls();
	m_Materials.update(std::move(materials));
	updateList();

	m_UpdTimer.Bind(wxEVT_TIMER, &FormMaterialsStages::OnUpdateTimer, this, m_UpdTimer.GetId());
	m_UpdTimer.Start(1000);
}

void EVE::Industry::FormMaterialsStages::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::FormMaterialsStages::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::FormMaterialsStages::createControls()
{
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);

	wxPanel* _btnPanel1 = new wxPanel(mainPanel);

	wxButton* btnCopyName = new wxButton(_btnPanel1, wxID_ANY, "copy name");
	btnCopyName->Bind(wxEVT_BUTTON, &FormMaterialsStages::OnCopyName, this);

	wxButton* btnCopyQuantity = new wxButton(_btnPanel1, wxID_ANY, "copy quantity");
	btnCopyQuantity->Bind(wxEVT_BUTTON, &FormMaterialsStages::OnCopyQuantity, this);

	wxBoxSizer* _btnPanel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	_btnPanel1Sizer->Add(btnCopyName, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1Sizer->Add(btnCopyQuantity, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1->SetSizer(_btnPanel1Sizer);

	m_VirtualList = new vListCtrl(
		mainPanel,
		std::make_unique<ListLayoutAvailableMaterials>(),
		&m_Materials,
		wxDefaultPosition,
		wxSize(200, 200));
	dynamic_cast<vListCtrl*>(m_VirtualList)->setIsImages(true);

	wxBoxSizer* mainPanelSizer = new wxBoxSizer(wxVERTICAL);
	mainPanelSizer->Add(_btnPanel1, 0, wxLEFT | wxTOP, 5);
	mainPanelSizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	mainPanel->SetSizer(mainPanelSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainPanel, 1, wxEXPAND);
	this->SetSizer(mainSizer);
}

void EVE::Industry::FormMaterialsStages::OnCopyName(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 0 });
}

void EVE::Industry::FormMaterialsStages::OnCopyQuantity(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 2 });
}

void EVE::Industry::FormMaterialsStages::OnUpdateTimer(wxTimerEvent& event)
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->OnUpdateTimer(event);

	event.Skip();
}
