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

#ifndef _EVEINDUSTRY_SOLARSYSTEMPANEL_HPP_
#define _EVEINDUSTRY_SOLARSYSTEMPANEL_HPP_

#include <string>
#include <format>
#include <memory>
#include <wx/wx.h>
#include <wx/textctrl.h>

#include "SolarSystemRecord.hpp"

namespace EVE::Industry
{

	class SolarSystemPanel : public wxPanel
	{
	public:
		explicit SolarSystemPanel(wxWindow* parent);
		~SolarSystemPanel() override = default;

		SolarSystemPanel(const SolarSystemPanel& tmp) = delete;
		SolarSystemPanel& operator=(const SolarSystemPanel& tmp) = delete;
		SolarSystemPanel(SolarSystemPanel&& tmp) = delete;
		SolarSystemPanel& operator=(SolarSystemPanel&& tmp) = delete;

		void bindRegionPanel(wxPanel* regionPanel);
		const SolarSystemRecord& get() const;

	private:
		void createControls();

		void OnClear(wxCommandEvent& event);
		void OnSelect(wxCommandEvent& event);

	private:
		wxTextCtrl* m_SolarSystemName{};
		wxPanel* m_RegionPanel{};
		SolarSystemRecord m_SolarSystem;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_SOLARSYSTEMPANEL_HPP_