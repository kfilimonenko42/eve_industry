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

#ifndef _EVEAPPSETTINGS_FORMSETTINGS_HPP_
#define _EVEAPPSETTINGS_FORMSETTINGS_HPP_

#include <wx/wx.h>
#include <wx/listbook.h>
#include <wx/sizer.h>

#include "DefaultSettings.hpp"
#include "Setting.hpp"
#include "EnumTools.hpp"

namespace EVE::APPSETTINGS
{

    class FormSettings : public wxDialog
    {
    public:
        explicit FormSettings(wxWindow* parent);
        ~FormSettings() override = default;

    private:
        void createControls();
        void addMainPage();

        void OnOk(wxCommandEvent& event);
        void OnCancel(wxCommandEvent& event);
        void formOk();
        void formCancel();

    private:
        wxListbook* m_ListBook{};
        wxArrayString m_arrAssetsLocalization;
        wxChoice* m_cAssetsLocalization{};
    };

} // EVE::APPSETTINGS

#endif // _EVEAPPSETTINGS_FORMSETTINGS_HPP_