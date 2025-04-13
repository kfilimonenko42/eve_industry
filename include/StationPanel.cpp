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

#include "StationPanel.hpp"
#include "FormSelectStation.hpp"
#include "RegionPanel.hpp"
#include "SolarSystemPanel.hpp"

EVE::Industry::StationPanel::StationPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	createControls();
}

void EVE::Industry::StationPanel::bindRegionPanel(wxPanel* regionPanel)
{
	if (regionPanel)
	{
		m_RegionPanel = regionPanel;
	}
}

void EVE::Industry::StationPanel::bindSolarSystemPanel(wxPanel* solSystemPanel)
{
	if (solSystemPanel)
	{
		m_SolarSystemPanel = solSystemPanel;
	}
}

const EVE::Industry::StationRecord& EVE::Industry::StationPanel::get() const
{
	return m_Station;
}

void EVE::Industry::StationPanel::createControls()
{
	wxStaticText* lblStationName = new wxStaticText(this, wxID_ANY, "Station: ", wxDefaultPosition, wxSize(50, 19));
	m_StationName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(220, 24), wxTE_READONLY);

	wxButton* m_btnClear = new wxButton(this, wxID_ANY, "x", wxDefaultPosition, wxSize(35, 24));
	m_btnClear->Bind(wxEVT_BUTTON, &StationPanel::OnClear, this);

	wxButton* m_btnSelect = new wxButton(this, wxID_ANY, "...", wxDefaultPosition, wxSize(35, 24));
	m_btnSelect->Bind(wxEVT_BUTTON, &StationPanel::OnSelect, this);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxHORIZONTAL);
	base_sizer->Add(lblStationName, 0, wxALL, 5);
	base_sizer->Add(m_StationName);
	base_sizer->Add(m_btnClear);
	base_sizer->Add(m_btnSelect);
	this->SetSizer(base_sizer);
}

void EVE::Industry::StationPanel::OnClear(wxCommandEvent& event)
{
	m_Station = StationRecord();
	m_StationName->Clear();
}

void EVE::Industry::StationPanel::OnSelect(wxCommandEvent& event)
{
	const std::uint32_t regionID = m_RegionPanel ? dynamic_cast<RegionPanel*>(m_RegionPanel)->get().id() : 0;
	const std::uint32_t solSystemID = m_SolarSystemPanel ? dynamic_cast<SolarSystemPanel*>(m_SolarSystemPanel)->get().id() : 0;
	std::unique_ptr<FormSelectStation> dialog = std::make_unique<FormSelectStation>(this, regionID, solSystemID);

	if (dialog->ShowModal() == wxID_OK)
	{
		m_Station = dialog->get();
		m_StationName->SetValue(m_Station.name());
	}
}
