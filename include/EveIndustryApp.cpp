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

#include "EveIndustryApp.hpp"
#include "FormApplication.hpp"

wxIMPLEMENT_APP(EVE::Industry::EVEIndustryApp);

bool EVE::Industry::EVEIndustryApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	m_Handle = new FormApplication();
	m_Handle->Show();
	
	dynamic_cast<FormApplication*>(m_Handle)->loadAssets();

	return true;
}

int EVE::Industry::EVEIndustryApp::OnExit()
{
	return wxApp::OnExit();
}