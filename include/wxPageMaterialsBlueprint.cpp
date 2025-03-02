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

#include "wxPageMaterialsBlueprint.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_MaterialsBlueprint.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::MaterialBlueprint>;

EVE::Industry::wxPageMaterialsBlueprint::wxPageMaterialsBlueprint(wxWindow* parent, ListDataWrapper<MaterialBlueprint>* materials)
	: wxWindow(parent, wxID_ANY), m_Parent{ parent }, m_Materials{ materials }
{
	createControls();
}

void EVE::Industry::wxPageMaterialsBlueprint::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::wxPageMaterialsBlueprint::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::wxPageMaterialsBlueprint::updatePrices()
{
	m_Materials->setPrices();
	refreshList();
}

void EVE::Industry::wxPageMaterialsBlueprint::updateImages()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	m_Materials->setImages(_list);
}

void EVE::Industry::wxPageMaterialsBlueprint::createControls()
{
	wxPanel* mainPanel = new wxPanel(m_Parent);

	wxPanel* _btnPanel1 = new wxPanel(mainPanel);

	wxButton* btnCopyNameQuantity = new wxButton(_btnPanel1, wxID_ANY, "copy (name + quantity)");
	btnCopyNameQuantity->Bind(wxEVT_BUTTON, &wxPageMaterialsBlueprint::OnCopyNameQuantity, this);

	wxButton* btnCopyName = new wxButton(_btnPanel1, wxID_ANY, "copy name");
	btnCopyName->Bind(wxEVT_BUTTON, &wxPageMaterialsBlueprint::OnCopyName, this);

	wxButton* btnCopyQuantity = new wxButton(_btnPanel1, wxID_ANY, "copy quantity");
	btnCopyQuantity->Bind(wxEVT_BUTTON, &wxPageMaterialsBlueprint::OnCopyQuantity, this);

	wxBoxSizer* _btnPanel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	_btnPanel1Sizer->Add(btnCopyNameQuantity, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1Sizer->Add(btnCopyName, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1Sizer->Add(btnCopyQuantity, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1->SetSizer(_btnPanel1Sizer);

	m_VirtualList = new vListCtrl(
		mainPanel,
		std::make_unique<ListLayoutMaterialsBlueprint>(),
		&m_Materials->get(),
		wxDefaultPosition,
		wxSize(200, 200));

	std::function<void()> updatePricesMethod = std::bind(&wxPageMaterialsBlueprint::updatePrices, this);
	std::function<void()> updateImageMethod = std::bind(&wxPageMaterialsBlueprint::updateImages, this);

	m_Materials->addUpdater(std::make_unique<PriceUpdater>(updatePricesMethod, m_EsiSettings));
	m_Materials->addUpdater(std::make_unique<ImagesUpdater>(updateImageMethod));
	m_Materials->setEsiSettings(m_EsiSettings);

	wxBoxSizer* mainPanelSizer = new wxBoxSizer(wxVERTICAL);
	mainPanelSizer->Add(_btnPanel1, 0, wxLEFT | wxTOP, 5);
	mainPanelSizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	mainPanel->SetSizer(mainPanelSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainPanel, 1, wxEXPAND);
	m_Parent->SetSizer(mainSizer);
}

void EVE::Industry::wxPageMaterialsBlueprint::OnCopyNameQuantity(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 0, 3 });
}

void EVE::Industry::wxPageMaterialsBlueprint::OnCopyName(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 0 });
}

void EVE::Industry::wxPageMaterialsBlueprint::OnCopyQuantity(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 3 });
}
