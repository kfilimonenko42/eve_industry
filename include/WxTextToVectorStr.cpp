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

#include "WxTextToVectorStr.hpp"

#include "StringTools.hpp"

void EVE::Industry::WxTextToVectorStr::operator()(const wxTextCtrl* text, std::vector<std::string>& dst)
{
	int lines = text->GetNumberOfLines();
	for (int index = 0; index < lines; ++index)
	{
        std::string tmp = tolower(text->GetLineText(index).utf8_string());
        if (!tmp.empty())
        {
            dst.push_back(std::move(tmp));
        }
	}
}