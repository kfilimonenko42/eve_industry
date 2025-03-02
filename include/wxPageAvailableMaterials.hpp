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

#ifndef _EVEINDUSTRY_WX_PAGEAVAILABLEMATERIALS_HPP_
#define _EVEINDUSTRY_WX_PAGEAVAILABLEMATERIALS_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <format>
#include <functional>
#include <wx/wx.h>
#include <wx/listctrl.h>

#include "MaterialProject.hpp"
#include "ListDataWrapper.hpp"

namespace EVE::Industry
{

	class wxPageAvailableMaterials : public wxWindow
	{
	public:
		wxPageAvailableMaterials(wxWindow* parent, wxWindow* formProject, ListDataWrapper<MaterialProject>* materials);
		~wxPageAvailableMaterials() override = default;

		wxPageAvailableMaterials(const wxPageAvailableMaterials& tmp) = delete;
		wxPageAvailableMaterials& operator=(const wxPageAvailableMaterials& tmp) = delete;
		wxPageAvailableMaterials(wxPageAvailableMaterials&& tmp) = delete;
		wxPageAvailableMaterials& operator=(wxPageAvailableMaterials&& tmp) = delete;

		void updateList();
		void refreshList();
		void updateImages();

	private:
		void createControls();

		void OnAdd(wxCommandEvent& event);
		void OnDelete(wxCommandEvent& event);
		void OnDeleteAll(wxCommandEvent& event);

	private:
		wxWindow* m_Parent{};
		wxWindow* m_FormProject{};
		wxListCtrl* m_VirtualList{};
		wxStaticText* m_TotalPriceSell{};
		wxStaticText* m_TotalPriceBuy{};

		ListDataWrapper<MaterialProject>* m_Materials;
	};

}

#endif // _EVEINDUSTRY_WX_PAGEAVAILABLEMATERIALS_HPP_