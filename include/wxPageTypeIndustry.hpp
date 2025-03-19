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

#ifndef _EVEINDUSTRY_WX_PAGETYPEINDUSTRY_HPP_
#define _EVEINDUSTRY_WX_PAGETYPEINDUSTRY_HPP_

#include <vector>
#include <thread>
#include <atomic>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/timer.h>

#include "TypeRecord.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_TypeManufacturing.hpp"
#include "TypeManufacturing.hpp"
#include "ListDataWrapper.hpp"
#include "Assets.hpp"

namespace EVE::Industry
{

	class wxPageTypeIndustry : public wxWindow
	{
	public:
		wxPageTypeIndustry(
			const TypeRecord& type,
			wxWindow* parent);
		~wxPageTypeIndustry() override = default;

		wxPageTypeIndustry(const wxPageTypeIndustry& tmp) = delete;
		wxPageTypeIndustry& operator=(const wxPageTypeIndustry& tmp) = delete;
		wxPageTypeIndustry(wxPageTypeIndustry&& tmp) = delete;
		wxPageTypeIndustry& operator=(wxPageTypeIndustry&& tmp) = delete;

		void updateList();
		void refreshList();

	private:
		void updateManufacturingMaterials();
		void createControls();
		void OnUpdateTimer(wxTimerEvent& event);

	private:
		TypeRecord m_Type;
		wxPanel* m_MainPanel{};
		wxListCtrl* m_VirtualList{};
		wxTimer m_UpdTimer;
		ListDataWrapper<TypeManufacturing> m_ManufacturingMaterials;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_WX_PAGETYPEINDUSTRY_HPP_