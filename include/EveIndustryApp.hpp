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

#ifndef _EVEINDUSTRY_MAIN_APP_HPP_
#define _EVEINDUSTRY_MAIN_APP_HPP_

#include <memory>
#include <wx/wx.h>

namespace EVE::Industry
{

	class EVEIndustryApp : public wxApp
	{
	public:
		EVEIndustryApp() = default;

		bool OnInit() override;
		int OnExit() override;

	private:
		wxFrame* m_Handle{};
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_MAIN_APP_HPP_