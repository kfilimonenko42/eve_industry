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

#include "FormSelectStation.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListBoxLayoutBox_Station.hpp"
#include "ListOfStations.hpp"
#include "StringTools.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::StationRecord>;

EVE::Industry::FormSelectStation::FormSelectStation(
	wxWindow* parent,
	const std::uint32_t regionID,
	const std::uint32_t solSystemID)
	: wxDialog(parent, wxID_ANY, "Station"), m_RegionID{ regionID }, m_SolarSystemID{ solSystemID }
{
	createControls();
	updateStationsList();
}

void EVE::Industry::FormSelectStation::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::FormSelectStation::select()
{
	formOk();
}

const EVE::Industry::StationRecord& EVE::Industry::FormSelectStation::get() const
{
	return m_Result;
}

void EVE::Industry::FormSelectStation::createControls()
{
	wxPanel* m_controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
	m_controlPanel->Bind(wxEVT_CHAR_HOOK, &FormSelectStation::OnKeyDown, this);

	wxStaticText* lblFilter = new wxStaticText(m_controlPanel, wxID_ANY, "Filter: ");
	m_txtFilter = new wxTextCtrl(m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(350, 24));
	m_txtFilter->Bind(wxEVT_TEXT, &FormSelectStation::OnFilterText, this);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_sizer->Add(lblFilter, 0, wxALL, 5);
	panel_sizer->AddStretchSpacer();
	panel_sizer->Add(m_txtFilter, 0, wxEXPAND, 5);
	m_controlPanel->SetSizer(panel_sizer);

	const Assets& assets = Assets::Instance();
	m_VirtualList = new vListCtrl(
		this,
		std::make_unique<ListLayoutBoxStationRecord>(this),
		&m_StationsList,
		wxDefaultPosition,
		wxSize(400, 300));
	dynamic_cast<vListCtrl*>(m_VirtualList)->singleSelection(true);

	wxPanel* m_btnPanel = new wxPanel(this, wxID_ANY);
	wxButton* m_btnOK = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btnOK->Bind(wxEVT_BUTTON, &FormSelectStation::OnOk, this);
	wxButton* m_btnCancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btnCancel->Bind(wxEVT_BUTTON, &FormSelectStation::OnCancel, this);

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

void EVE::Industry::FormSelectStation::updateStationsList()
{
	const std::string txtFilter = tolower(m_txtFilter->GetValue().ToStdString());
	FilterLeftStations filter{ m_RegionID, m_SolarSystemID, true };
	filter(m_StationsList, txtFilter);
	updateList();
}

void EVE::Industry::FormSelectStation::OnFilterText(wxCommandEvent& event)
{
	updateStationsList();
}

void EVE::Industry::FormSelectStation::OnOk(wxCommandEvent& event)
{
	formOk();
}

void EVE::Industry::FormSelectStation::OnCancel(wxCommandEvent& event)
{
	formCancel();
}

void EVE::Industry::FormSelectStation::OnKeyDown(wxKeyEvent& event)
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

void EVE::Industry::FormSelectStation::formOk()
{
	const std::vector<long> selected = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	if (selected.empty())
	{
		return;
	}

	const long index = selected[0];
	if (m_StationsList.size() > index)
	{
		m_Result = m_StationsList[index];
	}

	EndModal(wxID_OK);
}

void EVE::Industry::FormSelectStation::formCancel()
{
	EndModal(wxID_CLOSE);
}
