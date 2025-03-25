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

#ifndef _EVEAPPSETTINGS_SETTINGS_HPP_
#define _EVEAPPSETTINGS_SETTINGS_HPP_

#include <cstdint>
#include <filesystem>
#include <iostream>

#include "DefaultSettings.hpp"
#include "JsonHelper.hpp"

namespace EVE::APPSETTINGS
{

    class Settings
    {
    public:
        Settings();

        static Settings& Instance();

        const std::string& locTag() const;
        std::uint32_t solarSystem() const;

    private:
        std::string m_LocTag{ Default::LocTag };
        std::uint32_t m_SolarSystem{};

    private:
        void load(const std::string& settings_path);
    };

}

#endif // _EVEAPPSETTINGS_SETTINGS_HPP_