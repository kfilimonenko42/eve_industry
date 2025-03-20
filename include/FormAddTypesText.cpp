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

#include "FormAddTypesText.hpp"
#include "WxTextToVectorStr.hpp"
#include "Assets.hpp"

EVE::Industry::FormAddTypesText::FormAddTypesText(wxWindow* parent, const std::string& title)
	: wxDialog(parent, wxID_ANY, title)
{
	createControls();
}

std::vector<std::string> EVE::Industry::FormAddTypesText::get()
{
	return std::move(m_Result);
}

void EVE::Industry::FormAddTypesText::createControls()
{
	wxPanel* m_controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
	m_controlPanel->Bind(wxEVT_CHAR_HOOK, &FormAddTypesText::OnKeyDown, this);

	wxPanel* m_btnPanel = new wxPanel(this, wxID_ANY);

#if _DEBUG
	wxButton* m_btnAddAllTypes = new wxButton(this, wxID_ANY, "add all types", wxDefaultPosition, wxDefaultSize);
	m_btnAddAllTypes->Bind(wxEVT_BUTTON, &FormAddTypesText::OnAddAllTypes, this);
#endif

	m_TypesText = new wxTextCtrl(m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(800, 600), wxTE_MULTILINE | wxTE_RICH2 | wxTE_NOHIDESEL | wxTE_PROCESS_TAB);
	//m_TypesText->SetBackgroundColour(wxLIST_BACK_COLOUR_NIGHT);
	//m_TypesText->SetForegroundColour(wxLIST_FORE_COLOUR_NIGHT);

	wxButton* m_btn_Ok = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btn_Ok->Bind(wxEVT_BUTTON, &FormAddTypesText::OnOk, this);

	wxButton* m_btn_Cancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btn_Cancel->Bind(wxEVT_BUTTON, &FormAddTypesText::OnCancel, this);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(m_btn_Ok);
	btn_sizer->AddStretchSpacer();
	btn_sizer->Add(m_btn_Cancel);
	m_btnPanel->SetSizer(btn_sizer);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxVERTICAL);
#if _DEBUG
	base_sizer->Add(m_btnAddAllTypes, 0);
#endif
	base_sizer->Add(m_controlPanel, 1, wxEXPAND | wxALL, 5);
	base_sizer->Add(m_btnPanel, 0, wxALIGN_RIGHT | wxALL, 5);

	this->SetSizerAndFit(base_sizer);
}

void EVE::Industry::FormAddTypesText::OnOk(wxCommandEvent& event)
{
	formOk();
}

void EVE::Industry::FormAddTypesText::OnCancel(wxCommandEvent& event)
{
	formCancel();
}

void EVE::Industry::FormAddTypesText::OnKeyDown(wxKeyEvent& event)
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

#if _DEBUG
void EVE::Industry::FormAddTypesText::OnAddAllTypes(wxCommandEvent& event)
{
	const Assets& assets = Assets::Instance();
	for (auto ittr = assets.m_TypesContainer.cbegin(); ittr != assets.m_TypesContainer.cend(); ++ittr)
	{
		if (ittr->m_BlueprintID == 0)
		{
			continue;
		}

		m_TypesText->AppendText(std::format("{} 1\n", ittr->m_Name));
	}
}
#endif

void EVE::Industry::FormAddTypesText::formOk()
{
	m_Result.clear();

	EVE::Industry::WxTextToVectorStr textToVector{};
	textToVector(m_TypesText, m_Result);

	EndModal(wxID_OK);
}

void EVE::Industry::FormAddTypesText::formCancel()
{
	EndModal(wxID_CLOSE);
}
