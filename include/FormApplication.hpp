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

#ifndef _EVEINDUSTRY_FORMAPPLICATION_HPP_
#define _EVEINDUSTRY_FORMAPPLICATION_HPP_

#include <string>
#include <memory>
#include <functional>
#include <format>
#include <future>
#include <cstdint>
#include <wx/wx.h>
#include <wx/progdlg.h>
#include <wx/aboutdlg.h>
#include <wx/filename.h>
#include <wx/imagpng.h>
#include <wx/aui/auibook.h>
#include <wx/busyinfo.h>
#include <nlohmann/json.hpp>

namespace EVE::Industry
{

	class FormApplication : public wxFrame
	{
	public:
		FormApplication();

		void loadAssets();
		void OnUpdateCurrentPageText();

	private:
		void createControls();
		void createMenuBar();

		void OnNewProject(wxCommandEvent& e);
		void OnOpenProject(wxCommandEvent& e);
		void OnSaveProject(wxCommandEvent& e);
		void OnSaveAsProject(wxCommandEvent& e);
		void OnQuit(wxCommandEvent& e);
		void OnAbout(wxCommandEvent& e);
		void OnAppraisal(wxCommandEvent& e);

	private:
		wxMenuBar* m_MenuBar{};
		wxAuiNotebook* m_MainBook{};
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMAPPLICATION_HPP_