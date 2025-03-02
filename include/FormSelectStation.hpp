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

#ifndef _EVEINDUSTRY_FORMSELECTSTATION_HPP_
#define _EVEINDUSTRY_FORMSELECTSTATION_HPP_

#include <string>
#include <format>
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>

#include "wxVirtualListCtrl.hpp"
#include "StationRecord.hpp"

namespace EVE::Industry
{

	class FormSelectStation : public wxDialog
	{
	public:
		explicit FormSelectStation(
			wxWindow* parent,
			const std::uint32_t regionID = 0,
			const std::uint32_t solSystemID = 0);
		~FormSelectStation() override = default;

		FormSelectStation(const FormSelectStation& tmp) = delete;
		FormSelectStation& operator=(const FormSelectStation& tmp) = delete;
		FormSelectStation(FormSelectStation&& tmp) = delete;
		FormSelectStation& operator=(FormSelectStation&& tmp) = delete;

		void updateList();
		void select();

		const StationRecord& get() const;

	private:
		void createControls();
		void updateStationsList();

		void OnFilterText(wxCommandEvent& event);
		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void formOk();
		void formCancel();

	private:
		wxTextCtrl* m_txtFilter{};
		wxListCtrl* m_VirtualList{};
		std::uint32_t m_RegionID{};
		std::uint32_t m_SolarSystemID{};
		StationRecord m_Result;
		std::vector<StationRecord> m_StationsList;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMSELECTSTATION_HPP_