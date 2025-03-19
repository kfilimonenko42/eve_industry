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

#ifndef _EVEINDUSTRY_WX_PAGEPRODUCTIONSTAGES_HPP_
#define _EVEINDUSTRY_WX_PAGEPRODUCTIONSTAGES_HPP_

#include <memory>
#include <utility>
#include <format>
#include <thread>
#include <atomic>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/timer.h>

#include "ProductionStage.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_ProductionStages.hpp"
#include "ListDataWrapper.hpp"
#include "FormProject.hpp"
#include "TotalValues.hpp"

namespace EVE::Industry
{

	class wxPageProductionStages : public wxWindow
	{
	public:
		wxPageProductionStages(wxWindow* parent, wxWindow* formProject, ListDataWrapper<ProductionStage>* stages);
		~wxPageProductionStages() override = default;

		wxPageProductionStages(const wxPageProductionStages& tmp) = delete;
		wxPageProductionStages& operator=(const wxPageProductionStages& tmp) = delete;
		wxPageProductionStages(wxPageProductionStages&& tmp) = delete;
		wxPageProductionStages& operator=(wxPageProductionStages&& tmp) = delete;

		void updateList();
		void refreshList();

	private:
		void createControls();
		void updateTotalLabels();

		void OnCopyName(wxCommandEvent& event);
		void OnCopyRuns(wxCommandEvent& event);
		void OnListRightClick(wxListEvent& event);
		void OnListPopupClick(wxCommandEvent& event);
		void OnUpdateTimer(wxTimerEvent& event);

	private:
		wxWindow* m_Parent{};
		wxWindow* m_FormProject{};
		wxListCtrl* m_VirtualList{};
		wxStaticText* m_TotalStatuses{};
		wxTimer m_UpdTimer;
		ListDataWrapper<ProductionStage>* m_ProductionStages;
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_WX_PAGEPRODUCTIONSTAGES_HPP_