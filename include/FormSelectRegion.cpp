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

#include "FormSelectRegion.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListBoxLayoutBox_Region.hpp"
#include "ListOfRegions.hpp"
#include "StringTools.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::BaseRecord>;

EVE::Industry::FormSelectRegion::FormSelectRegion(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "Region")
{
	createControls();
	updateRegionList();
}

void EVE::Industry::FormSelectRegion::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::FormSelectRegion::select()
{
	formOk();
}

const EVE::Industry::BaseRecord& EVE::Industry::FormSelectRegion::get() const
{
	return m_Result;
}

void EVE::Industry::FormSelectRegion::createControls()
{
	wxPanel* m_controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
	m_controlPanel->Bind(wxEVT_CHAR_HOOK, &FormSelectRegion::OnKeyDown, this);

	wxStaticText* lblFilter = new wxStaticText(m_controlPanel, wxID_ANY, "Filter: ");
	m_txtFilter = new wxTextCtrl(m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(350, 24));
	m_txtFilter->Bind(wxEVT_TEXT, &FormSelectRegion::OnFilterText, this);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_sizer->Add(lblFilter, 0, wxALL, 5);
	panel_sizer->AddStretchSpacer();
	panel_sizer->Add(m_txtFilter, 0, wxEXPAND, 5);
	m_controlPanel->SetSizer(panel_sizer);

	const Assets& assets = Assets::Instance();
	m_VirtualList = new vListCtrl(
		this,
		std::make_unique<ListLayoutBoxRegionRecord>(this),
		&m_RegionsList,
		wxDefaultPosition,
		wxSize(400, 300));
	dynamic_cast<vListCtrl*>(m_VirtualList)->singleSelection(true);

	wxPanel* m_btnPanel = new wxPanel(this, wxID_ANY);
	wxButton* m_btnOK = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btnOK->Bind(wxEVT_BUTTON, &FormSelectRegion::OnOk, this);
	wxButton* m_btnCancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btnCancel->Bind(wxEVT_BUTTON, &FormSelectRegion::OnCancel, this);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(m_btnOK);
	btn_sizer->AddStretchSpacer();
	btn_sizer->Add(m_btnCancel);
	m_btnPanel->SetSizer(btn_sizer);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxVERTICAL);
	base_sizer->Add(m_controlPanel, 0, wxALL, 5);
	base_sizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	base_sizer->Add(m_btnPanel, 0, wxALIGN_RIGHT | wxALL, 5);

	this->SetSizerAndFit(base_sizer);
}

void EVE::Industry::FormSelectRegion::updateRegionList()
{
	const std::string txtFilter = tolower(m_txtFilter->GetValue().ToStdString());

	std::vector<BaseRecord> _list = m_RegionsList.copy();
	FilterRegions filter{ true };
	filter(_list, txtFilter);
	m_RegionsList.update(std::move(_list));
	updateList();
}

void EVE::Industry::FormSelectRegion::OnFilterText(wxCommandEvent& event)
{
	updateRegionList();
}

void EVE::Industry::FormSelectRegion::OnOk(wxCommandEvent& event)
{
	formOk();
}

void EVE::Industry::FormSelectRegion::OnCancel(wxCommandEvent& event)
{
	formCancel();
}

void EVE::Industry::FormSelectRegion::OnKeyDown(wxKeyEvent& event)
{
	int _key = (int)event.GetKeyCode();

	switch (_key)
	{
	case WXK_RETURN:
	{
		if (wxGetKeyState(WXK_CONTROL))
		{
			formOk();
		}
		break;
	}
	case WXK_ESCAPE: formCancel(); break;
	}

	event.Skip();
}

void EVE::Industry::FormSelectRegion::formOk()
{
	const std::vector<long> selected = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	if (selected.empty())
	{
		return;
	}

	const long index = selected[0];
	if (m_RegionsList.size() > index)
	{
		m_Result = m_RegionsList[index];
	}

	EndModal(wxID_OK);
}

void EVE::Industry::FormSelectRegion::formCancel()
{
	EndModal(wxID_CLOSE);
}
