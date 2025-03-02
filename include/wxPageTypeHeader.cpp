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

#include "wxPageTypeHeader.hpp"
#include "BitmapContainer.hpp"

EVE::Industry::wxPageTypeHeader::wxPageTypeHeader(const TypeRecord& type, wxWindow* parent)
	: wxWindow(parent, wxID_ANY), m_Type{ type }
{
	m_MainPanel = new wxPanel(parent, wxID_ANY);

	createControls();
}

void EVE::Industry::wxPageTypeHeader::createControls()
{
	BitmapContainer& _bmp = BitmapContainer::Instance();
	_bmp.update32(m_Type.id());

	wxStaticBitmap* typeBitmap = new wxStaticBitmap(m_MainPanel, wxID_ANY,
		_bmp.get32(m_Type.id()),
		wxDefaultPosition, wxSize(32, 32));
	wxStaticText* typeNameText = new wxStaticText(m_MainPanel, wxID_ANY, m_Type.name());

	wxBoxSizer* typepanel_sizer = new wxBoxSizer(wxHORIZONTAL);
	typepanel_sizer->Add(typeBitmap, 0, wxALL, 10);
	typepanel_sizer->Add(typeNameText, 0, wxALL, 10);
	m_MainPanel->SetSizer(typepanel_sizer);

	wxBoxSizer* page_sizer = new wxBoxSizer(wxVERTICAL);
	page_sizer->Add(m_MainPanel, 1, wxEXPAND);
	m_MainPanel->GetParent()->SetSizer(page_sizer);
}
