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

#ifndef _EVEINDUSTRY_REGIONPANEL_HPP_
#define _EVEINDUSTRY_REGIONPANEL_HPP_

#include <string>
#include <format>
#include <memory>
#include <wx/wx.h>
#include <wx/textctrl.h>

#include "BaseRecord.hpp"

namespace EVE::Industry
{

	class RegionPanel : public wxPanel
	{
	public:
		explicit RegionPanel(wxWindow* parent);
		~RegionPanel() override = default;

		RegionPanel(const RegionPanel& tmp) = delete;
		RegionPanel& operator=(const RegionPanel& tmp) = delete;
		RegionPanel(RegionPanel&& tmp) = delete;
		RegionPanel& operator=(RegionPanel&& tmp) = delete;

		const BaseRecord& get() const;

	private:
		void createControls();

		void OnClear(wxCommandEvent& event);
		void OnSelect(wxCommandEvent& event);

	private:
		wxTextCtrl* m_RegionName{};
		BaseRecord m_Region;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_REGIONPANEL_HPP_