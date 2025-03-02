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

#ifndef _EVEINDUSTRY_WX_PAGEMATERIALSBASE_HPP_
#define _EVEINDUSTRY_WX_PAGEMATERIALSBASE_HPP_

#include <memory>
#include <utility>
#include <format>
#include <wx/wx.h>
#include <wx/listctrl.h>

#include "MaterialBase.hpp"
#include "ListDataWrapper.hpp"
#include "EsiOrderSettings.hpp"

namespace EVE::Industry
{

	class wxPageMaterialsBase : public wxWindow
	{
	public:
		wxPageMaterialsBase(wxWindow* parent, ListDataWrapper<MaterialBase>* materials);
		~wxPageMaterialsBase() override = default;

		wxPageMaterialsBase(const wxPageMaterialsBase& tmp) = delete;
		wxPageMaterialsBase& operator=(const wxPageMaterialsBase& tmp) = delete;
		wxPageMaterialsBase(wxPageMaterialsBase&& tmp) = delete;
		wxPageMaterialsBase& operator=(wxPageMaterialsBase&& tmp) = delete;

		void updateList();
		void refreshList();
		void updatePrices();
		void updateImages();

	private:
		void createControls();
		void updateTotalLabels();

		void OnCopyNameQuantity(wxCommandEvent& event);
		void OnCopyName(wxCommandEvent& event);
		void OnCopyQuantity(wxCommandEvent& event);

	private:
		wxWindow* m_Parent{};
		wxListCtrl* m_VirtualList{};
		wxStaticText* m_TotalVolume{};
		wxStaticText* m_TotalPriceSell{};
		wxStaticText* m_TotalPriceBuy{};

		ListDataWrapper<MaterialBase>* m_Materials;
		EsiOrderSettings m_EsiSettings{};
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_WX_PAGEMATERIALSBASE_HPP_