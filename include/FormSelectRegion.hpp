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

#ifndef _EVEINDUSTRY_FORMSELECTREGION_HPP_
#define _EVEINDUSTRY_FORMSELECTREGION_HPP_

#include <string>
#include <format>
#include <cstdint>
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>

#include "ListDataWrapper.hpp"
#include "wxVirtualListCtrl.hpp"
#include "BaseRecord.hpp"

namespace EVE::Industry
{

	class FormSelectRegion : public wxDialog
	{
	public:
		explicit FormSelectRegion(wxWindow* parent);
		~FormSelectRegion() override = default;

		FormSelectRegion(const FormSelectRegion& tmp) = delete;
		FormSelectRegion& operator=(const FormSelectRegion& tmp) = delete;
		FormSelectRegion(FormSelectRegion&& tmp) = delete;
		FormSelectRegion& operator=(FormSelectRegion&& tmp) = delete;

		void updateList();
		void select();
		const BaseRecord& get() const;

	private:
		void createControls();
		void updateRegionList();

		void OnFilterText(wxCommandEvent& event);
		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void formOk();
		void formCancel();
		void OnClear(wxCommandEvent& event);

	private:
		wxTextCtrl* m_txtFilter{};
		wxListCtrl* m_VirtualList{};
		BaseRecord m_Result;
		ListDataWrapper<BaseRecord> m_RegionsList;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMSELECTREGION_HPP_