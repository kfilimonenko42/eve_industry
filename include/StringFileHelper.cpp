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

#include "StringFileHelper.hpp"

StringFileHelper::StringFileHelper(const std::string &fileName) : std::ifstream(fileName)
{
    if (!is_open())
    {
        throw std::runtime_error("Couldn't open file: " + fileName);
    }

	seekg(0, std::ios::end);
	m_sFileData.reserve(tellg());
	seekg(0, std::ios::beg);
	m_sFileData.assign(std::istreambuf_iterator<char>(*this), std::istreambuf_iterator<char>());
}

std::string StringFileHelper::get()
{
	return m_sFileData;
}