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

#ifndef _CLASS_JSON_HELPER_HPP_
#define _CLASS_JSON_HELPER_HPP_

#include <string>
#include <nlohmann/json.hpp>

#include "StringFileHelper.hpp"
#include "Logger.hpp"

class JsonHelper
{
public:
	explicit JsonHelper(std::string fileName);
	~JsonHelper() = default;

	bool load(nlohmann::json &result);
	bool save(const nlohmann::json &result);

private:
	std::string m_FileName;
};

#endif // _CLASS_JSON_HELPER_HPP_