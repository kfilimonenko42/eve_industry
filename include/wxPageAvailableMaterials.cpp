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

#include "wxPageAvailableMaterials.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_AvailableMaterials.hpp"
#include "FormProject.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::MaterialProject>;

EVE::Industry::wxPageAvailableMaterials::wxPageAvailableMaterials(
	wxWindow* parent,
	wxWindow* formProject,
	ListDataWrapper<MaterialProject>* materials)
	: wxWindow(parent, wxID_ANY), m_Parent{ parent }, m_FormProject{ formProject }, m_Materials{ materials }
{
	createControls();
}

void EVE::Industry::wxPageAvailableMaterials::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::wxPageAvailableMaterials::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::wxPageAvailableMaterials::updateImages()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	m_Materials->setImages(_list);
}

void EVE::Industry::wxPageAvailableMaterials::createControls()
{
	wxPanel* mainPanel = new wxPanel(m_Parent);

	wxButton* btnAddType = new wxButton(mainPanel, wxID_ANY, "add");
	btnAddType->Bind(wxEVT_BUTTON, &wxPageAvailableMaterials::OnAdd, this);

	wxButton* btnDeleteType = new wxButton(mainPanel, wxID_ANY, "delete");
	btnDeleteType->Bind(wxEVT_BUTTON, &wxPageAvailableMaterials::OnDelete, this);

	wxButton* btnDeleteAllTypes = new wxButton(mainPanel, wxID_ANY, "delete all");
	btnDeleteAllTypes->Bind(wxEVT_BUTTON, &wxPageAvailableMaterials::OnDeleteAll, this);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(btnAddType, 0, wxLeft | wxBottom | wxTop, 5);
	btn_sizer->Add(btnDeleteType, 0, wxLeft | wxBottom | wxTop, 5);
	btn_sizer->Add(btnDeleteAllTypes, 0, wxLeft | wxBottom | wxTop, 5);

	m_VirtualList = new vListCtrl(
		mainPanel,
		std::make_unique<ListLayoutAvailableMaterials>(),
		&m_Materials->get(),
		wxDefaultPosition,
		wxSize(200, 200));

	std::function<void()> updateImageMethod = std::bind(&wxPageAvailableMaterials::updateImages, this);
	m_Materials->addUpdater(std::make_unique<ImagesUpdater>(updateImageMethod));

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel_sizer->Add(btn_sizer, 0, wxLEFT | wxTOP, 5);
	panel_sizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	mainPanel->SetSizer(panel_sizer);

	wxBoxSizer* page_sizer = new wxBoxSizer(wxVERTICAL);
	page_sizer->Add(mainPanel, 1, wxEXPAND);
	mainPanel->GetParent()->SetSizer(page_sizer);
}

void EVE::Industry::wxPageAvailableMaterials::OnAdd(wxCommandEvent& event)
{
	dynamic_cast<FormProject*>(m_FormProject)->addAvailableTypes();
}

void EVE::Industry::wxPageAvailableMaterials::OnDelete(wxCommandEvent& event)
{
	std::vector<long> selected = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	dynamic_cast<FormProject*>(m_FormProject)->deleteAvailableTypes(selected);
}

void EVE::Industry::wxPageAvailableMaterials::OnDeleteAll(wxCommandEvent& event)
{
	dynamic_cast<FormProject*>(m_FormProject)->deleteAllAvailableTypes();
}