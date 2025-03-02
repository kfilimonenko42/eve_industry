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

#include "wxPageTypePISchema.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_TypeManufacturing.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::TypeManufacturing>;

EVE::Industry::wxPageTypePISchema::wxPageTypePISchema(const TypeRecord& type, wxWindow* parent)
	: wxWindow(parent, wxID_ANY), m_Type{ type }
{
	m_MainPanel = new wxPanel(parent, wxID_ANY);

	createControls();
	updateManufacturingMaterials();
}

void EVE::Industry::wxPageTypePISchema::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::wxPageTypePISchema::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::wxPageTypePISchema::updateImages()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	m_ManufacturingMaterials.setImages(_list);
}

void EVE::Industry::wxPageTypePISchema::updateManufacturingMaterials()
{
	m_ManufacturingMaterials.clear();

	const Assets& assets = Assets::Instance();

	auto [pfound, pischema] = assets.m_PISchemasContainer.element(m_Type.id());
	if (!pfound)
	{
		return;
	}

	std::vector<TypeManufacturing> tmp;
	SetTypeManufacturingList(pischema->m_Materials, tmp);
	m_ManufacturingMaterials.update(std::move(tmp));
	updateList();
}

void EVE::Industry::wxPageTypePISchema::createControls()
{
	m_VirtualList = new vListCtrl(
		m_MainPanel,
		std::make_unique<ListLayoutTypeManufacturing>(),
		&m_ManufacturingMaterials.get(),
		wxDefaultPosition,
		wxSize(200, 200));

	std::function<void()> updateImageMethod = std::bind(&wxPageTypePISchema::updateImages, this);
	m_ManufacturingMaterials.addUpdater(std::make_unique<ImagesUpdater>(updateImageMethod));

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel_sizer->Add(m_VirtualList, 1, wxEXPAND);
	m_MainPanel->SetSizer(panel_sizer);

	wxBoxSizer* page_sizer = new wxBoxSizer(wxVERTICAL);
	page_sizer->Add(m_MainPanel, 1, wxEXPAND);
	m_MainPanel->GetParent()->SetSizer(page_sizer);
}