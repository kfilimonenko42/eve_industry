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

#ifndef _EVEINDUSTRY_VERSION_HPP_
#define _EVEINDUSTRY_VERSION_HPP_

#include <string>
#include <format>

#define MAJOR_VERSION	0
#define MINOR_VERSION	1
#define RELEASE_NUMBER	1
#define VERSION_STRING  std::format("{}.{}.{}", MAJOR_VERSION, MINOR_VERSION, RELEASE_NUMBER)
#define VERSION_NUMBER  MAJOR_VERSION * 10000 + MINOR_VERSION * 100 + RELEASE_NUMBER;
#define PROJECT_NAME_STRING	std::string("EVE industry")
#define SDE_DATE_STRING	std::string("SDE 2024.11.12")
#define GITHUB_RELEASE_ID 204400384
#define GITHUB_LINK std::string("https://github.com/kfilimonenko42/eve_industry")

#endif // _EVEINDUSTRY_VERSION_HPP_