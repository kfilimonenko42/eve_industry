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

#include "wxPageMaterialsProject.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::MaterialProject>;

EVE::Industry::wxPageMaterialsProject::wxPageMaterialsProject(
	wxWindow* parent,
	wxWindow* formProject,
	ListDataWrapper<MaterialProject>* materials)
	: wxWindow(parent, wxID_ANY), m_Parent{ parent }, m_FormProject{ formProject }, m_Materials{ materials }
{
	createControls();

	m_UpdTimer.Bind(wxEVT_TIMER, &wxPageMaterialsProject::OnUpdateTimer, this, m_UpdTimer.GetId());
	m_UpdTimer.Start(1000);
}

void EVE::Industry::wxPageMaterialsProject::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();

	updateTotalLabels();
}

void EVE::Industry::wxPageMaterialsProject::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::wxPageMaterialsProject::updateTotalLabels()
{
	m_TotalPriceSell->SetLabelText(std::format(std::locale(""), "Total Price (sell): {:.2Lf}", totalPriceSell(m_Materials->get())));
	m_TotalPriceBuy->SetLabelText(std::format(std::locale(""), "Total Price (buy): {:.2Lf}", totalPriceBuy(m_Materials->get())));
}

void EVE::Industry::wxPageMaterialsProject::createControls()
{
	wxPanel* mainPanel = new wxPanel(m_Parent);

	wxButton* btnAddType = new wxButton(mainPanel, wxID_ANY, "add");
	btnAddType->Bind(wxEVT_BUTTON, &wxPageMaterialsProject::OnAdd, this);

	wxButton* btnDeleteType = new wxButton(mainPanel, wxID_ANY, "delete");
	btnDeleteType->Bind(wxEVT_BUTTON, &wxPageMaterialsProject::OnDelete, this);

	wxButton* btnDeleteAllTypes = new wxButton(mainPanel, wxID_ANY, "delete all");
	btnDeleteAllTypes->Bind(wxEVT_BUTTON, &wxPageMaterialsProject::OnDeleteAll, this);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(btnAddType, 0, wxLeft | wxBottom | wxTop, 5);
	btn_sizer->Add(btnDeleteType, 0, wxLeft | wxBottom | wxTop, 5);
	btn_sizer->Add(btnDeleteAllTypes, 0, wxLeft | wxBottom | wxTop, 5);

	m_VirtualList = new vListCtrl(
		mainPanel,
		std::make_unique<ListLayoutMaterialsProject>(),
		m_Materials,
		wxDefaultPosition,
		wxSize(200, 200));
	dynamic_cast<vListCtrl*>(m_VirtualList)->setIsPrices(true);
	dynamic_cast<vListCtrl*>(m_VirtualList)->setIsImages(true);

	wxPanel* _panelResults = new wxPanel(mainPanel);

	wxFont font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	m_TotalPriceSell = new wxStaticText(_panelResults, wxID_ANY, "Total Price (sell): - ");
	m_TotalPriceSell->SetFont(font);
	m_TotalPriceBuy = new wxStaticText(_panelResults, wxID_ANY, "Total Price (buy): - ");
	m_TotalPriceBuy->SetFont(font);

	wxBoxSizer* _resultSizer = new wxBoxSizer(wxVERTICAL);
	_resultSizer->AddSpacer(5);
	_resultSizer->Add(m_TotalPriceSell, 0, wxEXPAND);
	_resultSizer->AddSpacer(5);
	_resultSizer->Add(m_TotalPriceBuy, 0, wxEXPAND);
	_resultSizer->AddSpacer(5);
	_panelResults->SetSizer(_resultSizer);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel_sizer->Add(btn_sizer, 0, wxLEFT | wxTOP, 5);
	panel_sizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	panel_sizer->Add(_panelResults, 0, wxEXPAND | wxLEFT | wxBottom | wxRight, 5);
	mainPanel->SetSizer(panel_sizer);

	wxBoxSizer* page_sizer = new wxBoxSizer(wxVERTICAL);
	page_sizer->Add(mainPanel, 1, wxEXPAND);
	mainPanel->GetParent()->SetSizer(page_sizer);
}

void EVE::Industry::wxPageMaterialsProject::OnAdd(wxCommandEvent& event)
{
	dynamic_cast<FormProject*>(m_FormProject)->addTypes();
	dynamic_cast<FormProject*>(m_FormProject)->getBlueprints();
}

void EVE::Industry::wxPageMaterialsProject::OnDelete(wxCommandEvent& event)
{
	std::vector<long> selected = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	dynamic_cast<FormProject*>(m_FormProject)->deleteTypes(selected);
	dynamic_cast<FormProject*>(m_FormProject)->getBlueprints();
}

void EVE::Industry::wxPageMaterialsProject::OnDeleteAll(wxCommandEvent& event)
{
	dynamic_cast<FormProject*>(m_FormProject)->deleteAllTypes();
	dynamic_cast<FormProject*>(m_FormProject)->getBlueprints();
}

void EVE::Industry::wxPageMaterialsProject::OnUpdateTimer(wxTimerEvent& event)
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	if (priceUpdOwner(_list->GetId(), _list->LastRefreshPrice()))
	{
		updateTotalLabels();
	}
	_list->OnUpdateTimer(event);

	event.Skip();
}
