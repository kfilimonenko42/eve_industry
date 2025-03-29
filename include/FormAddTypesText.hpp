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

#ifndef _EVEINDUSTRY_FORMADDTYPESTEXT_HPP_
#define _EVEINDUSTRY_FORMADDTYPESTEXT_HPP_

#include <string>
#include <format>
#include <wx/wx.h>
#include <wx/dialog.h>

#include "WxTextToVectorStr.hpp"
#include "Assets.hpp"
#include "ListDataWrapper.hpp"
#include "ListBoxLayoutBox_Type.hpp"
#include "wxVirtualListCtrl.hpp"
#include "TypeRecord.hpp"
#include "StringTools.hpp"
#include "ListOfTypes.hpp"
#include "FormSelectInt.hpp"

namespace EVE::Industry
{

	class FormAddTypesText : public wxDialog
	{
	public:
		FormAddTypesText(wxWindow* parent, const std::string& title);

		void updateList();
		void select();
		std::vector<std::string> get();

	private:
		void createControls();
		void updateTypesList();

		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);

#if _DEBUG
		void OnAddAllTypes(wxCommandEvent& event);
#endif

		void formOk();
		void formCancel();
		void OnFilterText(wxCommandEvent& event);

	private:
		wxListCtrl* m_VirtualList{};
		wxTextCtrl* m_txtFilter{};
		wxTextCtrl* m_TypesText{};
		std::vector<std::string> m_Result;
		ListDataWrapper<TypeRecord> m_TypesList;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMADDTYPESTEXT_HPP_