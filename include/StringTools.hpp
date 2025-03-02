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

#ifndef _STRINGTOOLS_HPP_
#define _STRINGTOOLS_HPP_

#include <string>
#include <cctype>
#include <algorithm>

inline std::string tolower(std::string source)
{
	std::transform(
		std::begin(source),
		std::end(source),
		std::begin(source),
		[](unsigned char c)
		{
			return std::tolower(c);
		}
	);

	return source;
}

inline void trim_left(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char ch) 
        {
            return !std::isspace(ch);
        })
    );
}

inline void trim_right(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char ch) 
        {
            return !std::isspace(ch);
        }).base(), s.end()
    );
}

inline void trim_lr(std::string& s)
{
    trim_left(s);
    trim_right(s);
}

#endif // _STRINGTOOLS_HPP_