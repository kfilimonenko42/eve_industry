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

#include "FormSelectRigME.hpp"
#include "EnumTools.hpp"

EVE::Industry::FormSelectRigME::FormSelectRigME(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "Struct ME")
{
	createControls();
}

EVE::Assets::RigME EVE::Industry::FormSelectRigME::get() const
{
	return m_Result;
}

void EVE::Industry::FormSelectRigME::createControls()
{
	wxPanel* m_controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
	m_controlPanel->Bind(wxEVT_CHAR_HOOK, &FormSelectRigME::OnKeyDown, this);

	wxStaticText* lblRigME = new wxStaticText(m_controlPanel, wxID_ANY, "Rig ME: ");

	for (const auto& _elem : EVE::Assets::arrRigME)
	{
		m_arrRigME.Add(_elem.second);
	}
	m_cRigME = new wxChoice(m_controlPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_arrRigME);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_sizer->Add(lblRigME, 0, wxALL, 5);
	panel_sizer->AddStretchSpacer();
	panel_sizer->Add(m_cRigME, 0, wxEXPAND, 5);
	m_controlPanel->SetSizer(panel_sizer);

	wxPanel* m_btnPanel = new wxPanel(this, wxID_ANY);
	wxButton* m_btnOK = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btnOK->Bind(wxEVT_BUTTON, &FormSelectRigME::OnOk, this);
	wxButton* m_btnCancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btnCancel->Bind(wxEVT_BUTTON, &FormSelectRigME::OnCancel, this);

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

void EVE::Industry::FormSelectRigME::OnOk(wxCommandEvent& event)
{
	formOk();
}

void EVE::Industry::FormSelectRigME::OnCancel(wxCommandEvent& event)
{
	formCancel();
}

void EVE::Industry::FormSelectRigME::OnKeyDown(wxKeyEvent& event)
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

void EVE::Industry::FormSelectRigME::formOk()
{
	auto _index = m_cRigME->GetSelection();
	if (_index == wxNOT_FOUND)
	{
		return;
	}

	const std::string value = m_cRigME->GetString(_index).ToStdString();
	enumFromString(EVE::Assets::arrRigME, value, m_Result);

	EndModal(wxID_OK);
}

void EVE::Industry::FormSelectRigME::formCancel()
{
	EndModal(wxID_CLOSE);
}
