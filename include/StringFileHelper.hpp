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

#ifndef _CLASS_STRING_FILE_HELPER_HPP_
#define _CLASS_STRING_FILE_HELPER_HPP_

#include <fstream>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <cassert>

class StringFileHelper : std::ifstream
{
public:
	explicit StringFileHelper(const std::string &fileName);
	~StringFileHelper() = default;

	StringFileHelper(const StringFileHelper &tmp) = delete;
	StringFileHelper& operator=(const StringFileHelper &tmp) = delete;
	StringFileHelper(StringFileHelper &&tmp) = delete;
	StringFileHelper& operator=(StringFileHelper &&tmp) = delete;
	
	[[nodiscard]] std::string get();

private:
	std::string m_sFileData;
};

#endif // _CLASS_STRING_FILE_HELPER_HPP_