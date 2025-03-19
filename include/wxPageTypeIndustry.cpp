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

#include "wxPageTypeIndustry.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::TypeManufacturing>;

EVE::Industry::wxPageTypeIndustry::wxPageTypeIndustry(const TypeRecord& type, wxWindow* parent)
	: wxWindow(parent, wxID_ANY), m_Type{ type }
{
	m_MainPanel = new wxPanel(parent, wxID_ANY);

	createControls();
	updateManufacturingMaterials();

	m_UpdTimer.Bind(wxEVT_TIMER, &wxPageTypeIndustry::OnUpdateTimer, this, m_UpdTimer.GetId());
	m_UpdTimer.Start(1000);
}

void EVE::Industry::wxPageTypeIndustry::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::wxPageTypeIndustry::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::wxPageTypeIndustry::updateManufacturingMaterials()
{
	m_ManufacturingMaterials.clear();

	const Assets& assets = Assets::Instance();

	auto [bfound, blueprint] = assets.m_BlueprintsContainer.element(m_Type.bpID());
	if (!bfound)
	{
		return;
	}

	std::vector<TypeManufacturing> tmp;
	SetTypeManufacturingList(blueprint->m_ManufacturingMaterials, tmp);
	m_ManufacturingMaterials.update(std::move(tmp));
	updateList();
}

void EVE::Industry::wxPageTypeIndustry::createControls()
{
	m_VirtualList = new vListCtrl(
		m_MainPanel,
		std::make_unique<ListLayoutTypeManufacturing>(),
		&m_ManufacturingMaterials,
		wxDefaultPosition,
		wxSize(200, 200));
	dynamic_cast<vListCtrl*>(m_VirtualList)->setIsImages(true);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel_sizer->Add(m_VirtualList, 1, wxEXPAND);
	m_MainPanel->SetSizer(panel_sizer);

	wxBoxSizer* page_sizer = new wxBoxSizer(wxVERTICAL);
	page_sizer->Add(m_MainPanel, 1, wxEXPAND);
	m_MainPanel->GetParent()->SetSizer(page_sizer);
}

void EVE::Industry::wxPageTypeIndustry::OnUpdateTimer(wxTimerEvent& event)
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->OnUpdateTimer(event);

	event.Skip();
}
