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

#include "FormSelectSolarSystem.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListBoxLayoutBox_SolarSystem.hpp"
#include "ListOfSolarSystems.hpp"
#include "StringTools.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::SolarSystemRecord>;

EVE::Industry::FormSelectSolarSystem::FormSelectSolarSystem(wxWindow* parent, const std::uint32_t regionID)
	: wxDialog(parent, wxID_ANY, "Solar System"), m_RegionID{ regionID }
{
	createControls();
	updateSolarSystemList();
}

void EVE::Industry::FormSelectSolarSystem::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::FormSelectSolarSystem::select()
{
	formOk();
}

const EVE::Industry::SolarSystemRecord& EVE::Industry::FormSelectSolarSystem::get() const
{
	return m_Result;
}

void EVE::Industry::FormSelectSolarSystem::createControls()
{
	wxPanel* m_controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
	m_controlPanel->Bind(wxEVT_CHAR_HOOK, &FormSelectSolarSystem::OnKeyDown, this);

	wxStaticText* lblFilter = new wxStaticText(m_controlPanel, wxID_ANY, "Filter: ");
	m_txtFilter = new wxTextCtrl(m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(350, 24));
	m_txtFilter->Bind(wxEVT_TEXT, &FormSelectSolarSystem::OnFilterText, this);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_sizer->Add(lblFilter, 0, wxALL, 5);
	panel_sizer->AddStretchSpacer();
	panel_sizer->Add(m_txtFilter, 0, wxEXPAND, 5);
	m_controlPanel->SetSizer(panel_sizer);

	const Assets& assets = Assets::Instance();
	m_VirtualList = new vListCtrl(
		this,
		std::make_unique<ListLayoutBoxSolarSystemRecord>(this),
		&m_SolarSystemsList,
		wxDefaultPosition,
		wxSize(400, 300));
	dynamic_cast<vListCtrl*>(m_VirtualList)->singleSelection(true);

	wxPanel* m_btnPanel = new wxPanel(this, wxID_ANY);
	wxButton* m_btnOK = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btnOK->Bind(wxEVT_BUTTON, &FormSelectSolarSystem::OnOk, this);
	wxButton* m_btnCancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btnCancel->Bind(wxEVT_BUTTON, &FormSelectSolarSystem::OnCancel, this);

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

void EVE::Industry::FormSelectSolarSystem::updateSolarSystemList()
{
	const std::string txtFilter = tolower(m_txtFilter->GetValue().ToStdString());

	std::vector<SolarSystemRecord> _list = m_SolarSystemsList.copy();
	FilterLeftSolarSystems filter{ m_RegionID, true };
	filter(_list, txtFilter);
	m_SolarSystemsList.update(std::move(_list));
	updateList();
}

void EVE::Industry::FormSelectSolarSystem::OnFilterText(wxCommandEvent& event)
{
	updateSolarSystemList();
}

void EVE::Industry::FormSelectSolarSystem::OnOk(wxCommandEvent& event)
{
	formOk();
}

void EVE::Industry::FormSelectSolarSystem::OnCancel(wxCommandEvent& event)
{
	formCancel();
}

void EVE::Industry::FormSelectSolarSystem::OnKeyDown(wxKeyEvent& event)
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

void EVE::Industry::FormSelectSolarSystem::formOk()
{
	const std::vector<long> selected = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	if (selected.empty())
	{
		return;
	}

	const long index = selected[0];
	if (m_SolarSystemsList.size() > index)
	{
		m_Result = m_SolarSystemsList[index];
	}

	EndModal(wxID_OK);
}

void EVE::Industry::FormSelectSolarSystem::formCancel()
{
	EndModal(wxID_CLOSE);
}
