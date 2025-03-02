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

#ifndef _EVEINDUSTRY_FORMSELECTMAXRUNS_HPP_
#define _EVEINDUSTRY_FORMSELECTMAXRUNS_HPP_

#include <string>
#include <format>
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/spinctrl.h>

#include "BlueprintMaterialEfficiency.hpp"

namespace EVE::Industry
{

	class FormSelectMaxRuns : public wxDialog
	{
	public:
		explicit FormSelectMaxRuns(wxWindow* parent);
		~FormSelectMaxRuns() override = default;

		FormSelectMaxRuns(const FormSelectMaxRuns& tmp) = delete;
		FormSelectMaxRuns& operator=(const FormSelectMaxRuns& tmp) = delete;
		FormSelectMaxRuns(FormSelectMaxRuns&& tmp) = delete;
		FormSelectMaxRuns& operator=(FormSelectMaxRuns&& tmp) = delete;

		std::uint64_t get() const;

	private:
		void createControls();

		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void formOk();
		void formCancel();

	private:
		wxSpinCtrl* m_MaximumRunsPerJob{};
		std::uint64_t m_Result;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMSELECTMAXRUNS_HPP_