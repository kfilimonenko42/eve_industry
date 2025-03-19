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

constexpr int ID_ADD_STOCK = 10001;

using vListCtrl = wxVirtualListCtrl<EVE::Industry::MaterialBlueprint>;

EVE::Industry::wxPageMaterialsBlueprint::wxPageMaterialsBlueprint(wxWindow* parent, wxWindow* formProject, ListDataWrapper<MaterialBlueprint>* materials)
	: wxWindow(parent, wxID_ANY), m_Parent{ parent }, m_FormProject{ formProject }, m_Materials{ materials }
{
	createControls();

	m_UpdTimer.Bind(wxEVT_TIMER, &wxPageMaterialsBlueprint::OnUpdateTimer, this, m_UpdTimer.GetId());
	m_UpdTimer.Start(1000);
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
		m_Materials,
		wxDefaultPosition,
		wxSize(200, 200));
	m_VirtualList->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &wxPageMaterialsBlueprint::OnListRightClick, this);
	dynamic_cast<vListCtrl*>(m_VirtualList)->setIsPrices(true);
	dynamic_cast<vListCtrl*>(m_VirtualList)->setIsImages(true);

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

void EVE::Industry::wxPageMaterialsBlueprint::OnListRightClick(wxListEvent& event)
{
	wxMenu menu;
	menu.Append(ID_ADD_STOCK, "Add to stock");
	menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &wxPageMaterialsBlueprint::OnListPopupClick, this);
	PopupMenu(&menu);

	event.Skip();
}

void EVE::Industry::wxPageMaterialsBlueprint::OnListPopupClick(wxCommandEvent& event)
{
	const std::vector<long> sLines = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	if (sLines.empty())
	{
		return;
	}

	switch (event.GetId())
	{
	case ID_ADD_STOCK:
		dynamic_cast<FormProject*>(m_FormProject)->addStockFromBpMaterials(sLines);
		break;
	}
}

void EVE::Industry::wxPageMaterialsBlueprint::OnUpdateTimer(wxTimerEvent& event)
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->OnUpdateTimer(event);

	event.Skip();
}
