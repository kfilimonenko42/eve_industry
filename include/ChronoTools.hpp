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

#ifndef _CHRONOTOOLS_HPP_
#define _CHRONOTOOLS_HPP_

#include <chrono>

using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;

[[nodiscard]] inline decltype(auto) difference_seconds(const time_point start, const time_point end)
{
	const auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	return diff.count();
}

[[nodiscard]] inline decltype(auto) difference_seconds_now(const time_point start)
{
	const auto now = std::chrono::high_resolution_clock::now();
	return difference_seconds(start, now);
}

#endif // _CHRONOTOOLS_HPP_