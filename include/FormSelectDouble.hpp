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

#ifndef _EVEINDUSTRY_FORMSELECTDOUBLE_HPP_
#define _EVEINDUSTRY_FORMSELECTDOUBLE_HPP_

#include <string>
#include <format>
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/spinctrl.h>

namespace EVE::Industry
{

	class FormSelectDouble : public wxDialog
	{
	public:
		FormSelectDouble(wxWindow* parent, const std::string& formTitle, const std::string& spinLabel, double min = 0.0, double max = 100.0);
		~FormSelectDouble() override = default;

		FormSelectDouble(const FormSelectDouble& tmp) = delete;
		FormSelectDouble& operator=(const FormSelectDouble& tmp) = delete;
		FormSelectDouble(FormSelectDouble&& tmp) = delete;
		FormSelectDouble& operator=(FormSelectDouble&& tmp) = delete;

		double get() const;

	private:
		void createControls(const std::string& spinTitle);

		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void formOk();
		void formCancel();

	private:
		wxSpinCtrlDouble* m_SpinCtrlDouble{};
		double m_Result{};
		double m_Min{};
		double m_Max{};
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMSELECTDOUBLE_HPP_