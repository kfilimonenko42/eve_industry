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

#ifndef _EVEINDUSTRY_WX_PAGEMATERIALSPROJECT_HPP_
#define _EVEINDUSTRY_WX_PAGEMATERIALSPROJECT_HPP_

#include <memory>
#include <utility>
#include <format>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/timer.h>

#include "MaterialProject.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_MaterialsProject.hpp"
#include "ListDataWrapper.hpp"
#include "EsiOrderSettings.hpp"
#include "FormProject.hpp"
#include "TotalValues.hpp"

namespace EVE::Industry
{

	class wxPageMaterialsProject : public wxWindow
	{
	public:
		wxPageMaterialsProject(wxWindow* parent, wxWindow* formProject, ListDataWrapper<MaterialProject>* materials);
		~wxPageMaterialsProject() override = default;

		wxPageMaterialsProject(const wxPageMaterialsProject& tmp) = delete;
		wxPageMaterialsProject& operator=(const wxPageMaterialsProject& tmp) = delete;
		wxPageMaterialsProject(wxPageMaterialsProject&& tmp) = delete;
		wxPageMaterialsProject& operator=(wxPageMaterialsProject&& tmp) = delete;

		void updateList();
		void refreshList();

	private:
		void createControls();
		void updateTotalLabels();

		void OnAdd(wxCommandEvent& event);
		void OnDelete(wxCommandEvent& event);
		void OnDeleteAll(wxCommandEvent& event);
		void OnUpdateTimer(wxTimerEvent& event);

	private:
		wxWindow* m_Parent{};
		wxWindow* m_FormProject{};
		wxListCtrl* m_VirtualList{};
		wxStaticText* m_TotalPriceSell{};
		wxStaticText* m_TotalPriceBuy{};
		wxTimer m_UpdTimer;
		ListDataWrapper<MaterialProject>* m_Materials;
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_WX_PAGEMATERIALSPROJECT_HPP_