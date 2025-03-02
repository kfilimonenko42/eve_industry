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

#ifndef _EVEINDUSTRY_WX_PAGEBLUEPRINTSPROJECT_HPP_
#define _EVEINDUSTRY_WX_PAGEBLUEPRINTSPROJECT_HPP_

#include <memory>
#include <utility>
#include <format>
#include <thread>
#include <atomic>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>

#include "BlueprintProject.hpp"
#include "ListDataWrapper.hpp"

namespace EVE::Industry
{

	class wxPageBlueprintsProject : public wxWindow
	{
	public:
		wxPageBlueprintsProject(wxWindow* parent, wxWindow* formProject, ListDataWrapper<BlueprintProject>* materials);
		~wxPageBlueprintsProject() override = default;

		wxPageBlueprintsProject(const wxPageBlueprintsProject& tmp) = delete;
		wxPageBlueprintsProject& operator=(const wxPageBlueprintsProject& tmp) = delete;
		wxPageBlueprintsProject(wxPageBlueprintsProject&& tmp) = delete;
		wxPageBlueprintsProject& operator=(wxPageBlueprintsProject&& tmp) = delete;

		void updateList();
		void refreshList();
		void updateImages();

	private:
		void createControls();

		void OnCalculateProject(wxCommandEvent& event);
		void OnListRightClick(wxListEvent& event);
		void OnListPopupClick(wxCommandEvent& event);

	private:
		wxWindow* m_Parent{};
		wxWindow* m_FormProject{};
		wxListCtrl* m_VirtualList{};

		ListDataWrapper<BlueprintProject>* m_Blueprints;
	};

}

#endif // _EVEINDUSTRY_WX_PAGEBLUEPRINTSPROJECT_HPP_