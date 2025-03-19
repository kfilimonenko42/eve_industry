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

#ifndef _EVEINDUSTRY_FORMSELECTSOLARSYSTEM_HPP_
#define _EVEINDUSTRY_FORMSELECTSOLARSYSTEM_HPP_

#include <string>
#include <format>
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>

#include "ListDataWrapper.hpp"
#include "wxVirtualListCtrl.hpp"
#include "SolarSystemRecord.hpp"

namespace EVE::Industry
{

	class FormSelectSolarSystem : public wxDialog
	{
	public:
		explicit FormSelectSolarSystem(wxWindow* parent, const std::uint32_t regionID = 0);
		~FormSelectSolarSystem() override = default;

		FormSelectSolarSystem(const FormSelectSolarSystem& tmp) = delete;
		FormSelectSolarSystem& operator=(const FormSelectSolarSystem& tmp) = delete;
		FormSelectSolarSystem(FormSelectSolarSystem&& tmp) = delete;
		FormSelectSolarSystem& operator=(FormSelectSolarSystem&& tmp) = delete;

		void updateList();
		void select();
		const SolarSystemRecord& get() const;

	private:
		void createControls();
		void updateSolarSystemList();

		void OnFilterText(wxCommandEvent& event);
		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void formOk();
		void formCancel();

	private:
		wxTextCtrl* m_txtFilter{};
		wxListCtrl* m_VirtualList{};
		SolarSystemRecord m_Result;
		std::uint32_t m_RegionID{};
		ListDataWrapper<SolarSystemRecord> m_SolarSystemsList;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMSELECTSOLARSYSTEM_HPP_