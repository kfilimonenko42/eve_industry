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

#include "FormProjectName.hpp"

EVE::Industry::FormProjectName::FormProjectName(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "enter project name")
{
	createControls();
}

std::string EVE::Industry::FormProjectName::get()
{
	return m_Result;
}

void EVE::Industry::FormProjectName::createControls()
{
	wxPanel* m_controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
	m_controlPanel->Bind(wxEVT_CHAR_HOOK, &FormProjectName::OnKeyDown, this);

	wxPanel* m_btnPanel = new wxPanel(this, wxID_ANY);

	wxStaticText* nameLabel = new wxStaticText(m_controlPanel, wxID_ANY, "Enter project name: ");
	m_ProjectName = new wxTextCtrl(m_controlPanel, wxID_ANY, "new project", wxDefaultPosition, wxDefaultSize, wxTE_RICH2 | wxTE_NOHIDESEL | wxTE_PROCESS_TAB | wxTE_PROCESS_ENTER);

	wxButton* m_btn_Ok = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btn_Ok->Bind(wxEVT_BUTTON, &FormProjectName::OnOk, this);
	
	wxButton* m_btn_Cancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btn_Cancel->Bind(wxEVT_BUTTON, &FormProjectName::OnCancel, this);

	wxBoxSizer* controlPanel_sizer = new wxBoxSizer(wxHORIZONTAL);
	controlPanel_sizer->SetMinSize(400, 25);
	controlPanel_sizer->Add(nameLabel, 0, wxALL, 5);
	controlPanel_sizer->Add(m_ProjectName, 1, wxEXPAND | wxALL, 5);
	m_controlPanel->SetSizer(controlPanel_sizer);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(m_btn_Ok);
	btn_sizer->AddStretchSpacer();
	btn_sizer->Add(m_btn_Cancel);
	m_btnPanel->SetSizer(btn_sizer);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxVERTICAL);
	base_sizer->Add(m_controlPanel, 1, wxEXPAND | wxALL, 5);
	base_sizer->Add(m_btnPanel, 0, wxALIGN_RIGHT | wxALL, 5);

	this->SetSizerAndFit(base_sizer);
}

void EVE::Industry::FormProjectName::OnOk(wxCommandEvent& event)
{	
	formOk();
}

void EVE::Industry::FormProjectName::OnCancel(wxCommandEvent& event)
{
	formCancel();
}

void EVE::Industry::FormProjectName::OnKeyDown(wxKeyEvent& event)
{
	int _key = (int)event.GetKeyCode();

	bool skip{ true };
	switch (_key)
	{
	case WXK_RETURN:
	{
		skip = false;
		formOk(); 
		break;
	}
	case WXK_ESCAPE: formCancel(); break;
	}

	if (skip)
	{
		event.Skip();
	}
}

void EVE::Industry::FormProjectName::formOk()
{
	m_Result = m_ProjectName->GetValue().ToStdString();

	if (m_Result.empty())
	{
		return;
	}

	EndModal(wxID_OK);
}

void EVE::Industry::FormProjectName::formCancel()
{
	EndModal(wxID_CLOSE);
}
