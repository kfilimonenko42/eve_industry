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

#ifndef _ENUMTOOLS_HPP_
#define _ENUMTOOLS_HPP_

#include <string>
#include <array>
#include <algorithm>

template<typename T>
inline void enumFromString(const auto& array, const std::string& src, T& result)
{
	auto ittr = std::find_if(std::begin(array), std::end(array),
		[&src](const std::pair<T, std::string>& elem)
		{
			return elem.second == src;
		});

	result = ((ittr != std::end(array)) ? ittr : std::begin(array))->first;
}

template<typename T>
inline std::string stringFromEnum(const auto& array, const T& src)
{
	auto ittr = std::find_if(std::begin(array), std::end(array),
		[&src](const std::pair<T, std::string>& elem)
		{
			return elem.first == src;
		});

	return ((ittr != std::end(array)) ? ittr : std::begin(array))->second;
}

#endif // _ENUMTOOLS_HPP_