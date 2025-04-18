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

#ifndef _EVEINDUSTRY_FORMSELECTBLUEPRINTME_HPP_
#define _EVEINDUSTRY_FORMSELECTBLUEPRINTME_HPP_

#include <string>
#include <format>
#include <wx/wx.h>
#include <wx/dialog.h>

#include "BlueprintMaterialEfficiency.hpp"

namespace EVE::Industry
{

	class FormSelectBlueprintME : public wxDialog
	{
	public:
		explicit FormSelectBlueprintME(wxWindow* parent);
		~FormSelectBlueprintME() override = default;

		FormSelectBlueprintME(const FormSelectBlueprintME& tmp) = delete;
		FormSelectBlueprintME& operator=(const FormSelectBlueprintME& tmp) = delete;
		FormSelectBlueprintME(FormSelectBlueprintME&& tmp) = delete;
		FormSelectBlueprintME& operator=(FormSelectBlueprintME&& tmp) = delete;

		EVE::Assets::BlueprintME get() const;

	private:
		void createControls();

		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void formOk();
		void formCancel();

	private:
		wxArrayString m_arrBpME;
		wxChoice* m_cBpME{};
		EVE::Assets::BlueprintME m_Result;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMSELECTBLUEPRINTME_HPP_