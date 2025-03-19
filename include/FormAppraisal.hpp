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

#ifndef _EVEINDUSTRY_FORMPAPPRAISAL_HPP_
#define _EVEINDUSTRY_FORMPAPPRAISAL_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <format>
#include <functional>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/timer.h>

#include "MaterialAppraisal.hpp"
#include "ListDataWrapper.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_MaterialsAppraisal.hpp"
#include "AppraisalContainer.hpp"
#include "BitmapContainer.hpp"
#include "WxTextToVectorStr.hpp"
#include "VectorStrToTypeIndustry.hpp"
#include "TotalValues.hpp"
#include "StringTools.hpp"
#include "RegionPanel.hpp"
#include "SolarSystemPanel.hpp"
#include "StationPanel.hpp"
#include "ChronoTools.hpp"

namespace EVE::Industry
{

	class FormAppraisal : public wxWindow
	{
	public:
		FormAppraisal(wxWindow* parent);
		~FormAppraisal() override = default;

		void updateList();
		void refreshList();

	private:
		void createControls();
		void updateTotalLabels();
		void OnSubmit(wxCommandEvent& event);
		void OnClear(wxCommandEvent& event);
		void OnUpdateTimer(wxTimerEvent& event);

	private:
		wxTextCtrl* m_TypesText{};
		wxListCtrl* m_VirtualList{};
		wxStaticText* m_TotalPriceSell{};
		wxStaticText* m_TotalPriceBuy{};
		wxPanel* m_RegionPanel;
		wxPanel* m_SolarSystemPanel;
		wxPanel* m_StationPanel;
		wxTimer m_UpdTimer;
		ListDataWrapper<MaterialAppraisal> m_Materials;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMPAPPRAISAL_HPP_