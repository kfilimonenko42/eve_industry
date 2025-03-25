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

#include "Setting.hpp"

EVE::APPSETTINGS::Settings::Settings()
{
    const std::string settings_path{ std::format("{}/settings.json", std::filesystem::current_path().string()) };
    if (std::filesystem::exists(settings_path))
    {
        load(settings_path);
    }
}

EVE::APPSETTINGS::Settings& EVE::APPSETTINGS::Settings::Instance()
{
    static Settings instance{};
    return instance;
}

const std::string& EVE::APPSETTINGS::Settings::locTag() const
{
    return this->m_LocTag;
}

std::uint32_t EVE::APPSETTINGS::Settings::solarSystem() const
{
    return this->m_SolarSystem;
}

void EVE::APPSETTINGS::Settings::load(const std::string& settings_path)
{
    JsonHelper jh(settings_path);

    nlohmann::json js;
    if (!jh.load(js)) { return; }

    if (js.contains("LocTag")) { js.at("LocTag").get_to(this->m_LocTag); }
    if (js.contains("SolarSystem")) { js.at("SolarSystem").get_to(this->m_SolarSystem); }
}
