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

#include "FormSelectDouble.hpp"

EVE::Industry::FormSelectDouble::FormSelectDouble(wxWindow* parent, const std::string& formTitle, const std::string& spinLabel, double min, double max)
	: wxDialog(parent, wxID_ANY, formTitle), m_Min{ min }, m_Max{ max }
{
	createControls(spinLabel);
}

double EVE::Industry::FormSelectDouble::get() const
{
	return m_Result;
}

void EVE::Industry::FormSelectDouble::createControls(const std::string& spinLabel)
{
	wxPanel* m_controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
	m_controlPanel->Bind(wxEVT_CHAR_HOOK, &FormSelectDouble::OnKeyDown, this);

	wxStaticText* lblSpin = new wxStaticText(m_controlPanel, wxID_ANY, spinLabel);
	m_SpinCtrlDouble = new wxSpinCtrlDouble(m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP, m_Min, m_Max, 0.0, 0.5);
	m_SpinCtrlDouble->SetDigits(1);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_sizer->Add(lblSpin, 0, wxALL, 5);
	panel_sizer->AddStretchSpacer();
	panel_sizer->Add(m_SpinCtrlDouble, 0, wxEXPAND, 5);
	m_controlPanel->SetSizer(panel_sizer);

	wxPanel* m_btnPanel = new wxPanel(this, wxID_ANY);
	wxButton* m_btnOK = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btnOK->Bind(wxEVT_BUTTON, &FormSelectDouble::OnOk, this);
	wxButton* m_btnCancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btnCancel->Bind(wxEVT_BUTTON, &FormSelectDouble::OnCancel, this);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(m_btnOK);
	btn_sizer->AddStretchSpacer();
	btn_sizer->Add(m_btnCancel);
	m_btnPanel->SetSizer(btn_sizer);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxVERTICAL);
	base_sizer->Add(m_controlPanel, 0, wxALL, 5);
	base_sizer->Add(m_btnPanel, 0, wxALIGN_RIGHT | wxALL, 5);

	this->SetSizerAndFit(base_sizer);
}

void EVE::Industry::FormSelectDouble::OnOk(wxCommandEvent& event)
{
	formOk();
}

void EVE::Industry::FormSelectDouble::OnCancel(wxCommandEvent& event)
{
	formCancel();
}

void EVE::Industry::FormSelectDouble::OnKeyDown(wxKeyEvent& event)
{
	int _key = (int)event.GetKeyCode();

	switch (_key)
	{
	case WXK_RETURN: formOk(); break;
	case WXK_ESCAPE: formCancel(); break;
	}

	event.Skip();
}

void EVE::Industry::FormSelectDouble::formOk()
{
	m_Result = m_SpinCtrlDouble->GetValue();

	EndModal(wxID_OK);
}

void EVE::Industry::FormSelectDouble::formCancel()
{
	EndModal(wxID_CLOSE);
}
