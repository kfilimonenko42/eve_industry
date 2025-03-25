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

#include "wxPageTypeDescription.hpp"

EVE::Industry::wxPageTypeDescription::wxPageTypeDescription(const TypeRecord& type, wxWindow* parent)
	: wxWindow(parent, wxID_ANY), m_Type{ type }
{
	m_MainPanel = new wxPanel(parent, wxID_ANY);

	createControls();
}

void EVE::Industry::wxPageTypeDescription::createControls()
{
	wxPanel* descriptionPanel = new wxPanel(m_MainPanel, wxID_ANY);
	wxTextCtrl* m_DescriptionText = new wxTextCtrl(descriptionPanel, wxID_ANY, wxString::FromUTF8(m_Type.description()),
		wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2 | wxTE_READONLY);

	wxBoxSizer* descriptionPanel_sizer = new wxBoxSizer(wxHORIZONTAL);
	descriptionPanel_sizer->Add(m_DescriptionText, 1, wxALL | wxEXPAND, 10);
	descriptionPanel->SetSizer(descriptionPanel_sizer);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel_sizer->Add(descriptionPanel, 1, wxEXPAND);
	m_MainPanel->SetSizer(panel_sizer);

	wxBoxSizer* page_sizer = new wxBoxSizer(wxVERTICAL);
	page_sizer->Add(m_MainPanel, 1, wxEXPAND);
	m_MainPanel->GetParent()->SetSizer(page_sizer);
}

