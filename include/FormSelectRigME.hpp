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

#ifndef _EVEINDUSTRY_FORMSELECTRIGME_HPP_
#define _EVEINDUSTRY_FORMSELECTRIGME_HPP_

#include <string>
#include <format>
#include <wx/wx.h>
#include <wx/dialog.h>

#include "BlueprintMaterialEfficiency.hpp"

namespace EVE::Industry
{

	class FormSelectRigME : public wxDialog
	{
	public:
		explicit FormSelectRigME(wxWindow* parent);
		~FormSelectRigME() override = default;

		FormSelectRigME(const FormSelectRigME& tmp) = delete;
		FormSelectRigME& operator=(const FormSelectRigME& tmp) = delete;
		FormSelectRigME(FormSelectRigME&& tmp) = delete;
		FormSelectRigME& operator=(FormSelectRigME&& tmp) = delete;

		EVE::Assets::RigME get() const;

	private:
		void createControls();

		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void formOk();
		void formCancel();

	private:
		wxArrayString m_arrRigME;
		wxChoice* m_cRigME{};
		EVE::Assets::RigME m_Result;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMSELECTRIGME_HPP_