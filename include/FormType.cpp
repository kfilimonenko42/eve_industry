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

#include "FormType.hpp"
#include "wxPageTypeHeader.hpp"
#include "wxPageTypeDescription.hpp"
#include "wxPageTypeIndustry.hpp"
#include "wxPageTypePISchema.hpp"

EVE::Industry::FormType::FormType(const TypeRecord& type, wxWindow* parent)
	: wxMiniFrame(parent, wxID_ANY, "type info", wxDefaultPosition, wxDefaultSize, wxCLOSE_BOX | wxCAPTION | wxRESIZE_BORDER),
	m_Type{ type }
{
	createControls();
}

void EVE::Industry::FormType::createControls()
{
	m_MainPanel = new wxPanel(this, wxID_ANY);
	m_HeaderPanel = new wxPanel(m_MainPanel, wxID_ANY);

	m_PageHeader = new wxPageTypeHeader(m_Type, m_HeaderPanel);

	m_baseNotebook = new wxNotebook(m_MainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	
	wxNotebookPage* page_description = new wxNotebookPage(m_baseNotebook, wxID_ANY);
	m_baseNotebook->AddPage(page_description, "Description");
	m_PageDescription = new wxPageTypeDescription(m_Type, page_description);

	if (m_Type.bpID() > 0)
	{
		wxNotebookPage* page_industry = new wxNotebookPage(m_baseNotebook, wxID_ANY);
		m_baseNotebook->AddPage(page_industry, "Industry");
		m_PageIndustry = new wxPageTypeIndustry(m_Type, page_industry);
	}

	EVE::Assets::IsTypePI isTypePI{};
	if (isTypePI(m_Type.group().id()))
	{
		wxNotebookPage* page_pischema = new wxNotebookPage(m_baseNotebook, wxID_ANY);
		m_baseNotebook->AddPage(page_pischema, "PI schema");
		m_PagePISchema = new wxPageTypePISchema(m_Type, page_pischema);
	}

	wxBoxSizer* formPanel_sizer = new wxBoxSizer(wxVERTICAL);
	formPanel_sizer->Add(m_HeaderPanel);
	formPanel_sizer->Add(m_baseNotebook, 1, wxEXPAND);
	m_MainPanel->SetSizer(formPanel_sizer);

	wxBoxSizer* top_sizer = new wxBoxSizer(wxHORIZONTAL);
	top_sizer->SetMinSize(600, 400);
	top_sizer->Add(m_MainPanel, 1, wxEXPAND);
	this->SetSizerAndFit(top_sizer);
}