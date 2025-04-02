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

using vListCtrl = wxVirtualListCtrl<EVE::Industry::TypeRecord>;

EVE::Industry::FormAddTypesText::FormAddTypesText(
	wxWindow* parent,
	const std::string& title,
	bool indyTypes)
	: wxDialog(parent, wxID_ANY, title), m_IndyTypes{ indyTypes }
{
	createControls();
	updateTypesList();
}

void EVE::Industry::FormAddTypesText::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::FormAddTypesText::select()
{
	const std::vector<long> selected = dynamic_cast<vListCtrl*>(m_VirtualList)->getSelected();
	if (selected.empty())
	{
		return;
	}

	const long index = selected[0];
	if (m_TypesList.size() > index)
	{
		const TypeRecord tmpType = m_TypesList[index];

		std::unique_ptr<FormSelectInt> dialog = std::make_unique<FormSelectInt>(this, tmpType.name(), "Quantity", 1, INT_MAX);

		if (dialog->ShowModal() == wxID_OK)
		{
			const std::uint64_t result = dialog->get();
			m_TypesText->AppendText(
				wxString::FromUTF8(std::format("{}\t{}\n", tmpType.name(), result)));
		}
	}
}

std::vector<std::string> EVE::Industry::FormAddTypesText::get()
{
	return std::move(m_Result);
}

int EVE::Industry::FormAddTypesText::getMultiplyBy() const
{
	return m_ResultMultiplyBy;
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

	wxPanel* m_middlePanel = new wxPanel(this, wxID_ANY);
	wxPanel* m_leftPanel = new wxPanel(m_middlePanel, wxID_ANY);
	wxPanel* m_rightPanel = new wxPanel(m_middlePanel, wxID_ANY);

	wxStaticText* lblFilter = new wxStaticText(m_leftPanel, wxID_ANY, "Filter: ");
	m_txtFilter = new wxTextCtrl(m_leftPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(350, 24));
	m_txtFilter->Bind(wxEVT_TEXT, &FormAddTypesText::OnFilterText, this);

	wxBoxSizer* filterSizer = new wxBoxSizer(wxHORIZONTAL);
	filterSizer->Add(lblFilter, 0, wxALL, 5);
	filterSizer->AddStretchSpacer();
	filterSizer->Add(m_txtFilter, 0, wxEXPAND, 5);

	m_VirtualList = new vListCtrl(
		m_leftPanel,
		std::make_unique<ListLayoutBoxTypeRecord>(this),
		&m_TypesList,
		wxDefaultPosition,
		wxSize(400, 570));
	dynamic_cast<vListCtrl*>(m_VirtualList)->singleSelection(true);

	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	leftSizer->Add(filterSizer, 0, wxALL, 5);
	leftSizer->AddStretchSpacer();
	leftSizer->Add(m_VirtualList);
	m_leftPanel->SetSizer(leftSizer);

	m_TypesText = new wxTextCtrl(m_rightPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(800, 600), wxTE_MULTILINE | wxTE_RICH2 | wxTE_NOHIDESEL | wxTE_PROCESS_TAB);

	wxBoxSizer* middleSizer = new wxBoxSizer(wxHORIZONTAL);
	middleSizer->Add(m_leftPanel);
	middleSizer->AddStretchSpacer();
	middleSizer->Add(m_rightPanel, 0, wxALL, 5);
	m_middlePanel->SetSizer(middleSizer);

	wxStaticText* lblMultiplayBy = new wxStaticText(m_btnPanel, wxID_ANY, "Multiply by: ");
	m_MultiplyBy = new wxSpinCtrl(m_btnPanel, wxID_ANY, "1", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP, 1, INT_MAX);
	wxButton* m_btn_Ok = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btn_Ok->Bind(wxEVT_BUTTON, &FormAddTypesText::OnOk, this);
	wxButton* m_btn_Cancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btn_Cancel->Bind(wxEVT_BUTTON, &FormAddTypesText::OnCancel, this);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(lblMultiplayBy, 0, wxTOP, 3);
	btn_sizer->Add(m_MultiplyBy, 0, wxRIGHT, 10);
	btn_sizer->Add(m_btn_Ok);
	btn_sizer->AddStretchSpacer();
	btn_sizer->Add(m_btn_Cancel);
	m_btnPanel->SetSizer(btn_sizer);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxVERTICAL);
#if _DEBUG
	base_sizer->Add(m_btnAddAllTypes, 0);
#endif
	base_sizer->Add(m_middlePanel, 1, wxALL, 5);
	base_sizer->Add(m_btnPanel, 0, wxALIGN_RIGHT | wxALL, 5);

	this->SetSizerAndFit(base_sizer);
}

void EVE::Industry::FormAddTypesText::updateTypesList()
{
	const std::string txtFilter = tolower(m_txtFilter->GetValue().utf8_string());

	std::vector<TypeRecord> _list = m_TypesList.copy();
	FilterTypes filter{ m_IndyTypes, true };
	filter(_list, txtFilter);
	m_TypesList.update(std::move(_list));
	updateList();
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

	m_ResultMultiplyBy = m_MultiplyBy->GetValue();

	EndModal(wxID_OK);
}

void EVE::Industry::FormAddTypesText::formCancel()
{
	EndModal(wxID_CLOSE);
}

void EVE::Industry::FormAddTypesText::OnFilterText(wxCommandEvent& event)
{
	updateTypesList();
}
