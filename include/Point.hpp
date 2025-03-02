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

#ifndef _EVEASSETS_POINT_HPP_
#define _EVEASSETS_POINT_HPP_

#include <iostream>
#include <format>

namespace EVE::Assets
{

	class Point
	{
	public:
		Point() = default;
		Point(double _x, double _y, double _z);

		Point& operator+=(double numb);
		Point& operator-=(double numb);
		Point& operator*=(double numb);
		Point& operator/=(double numb);

	public:
		double m_X{};
		double m_Y{};
		double m_Z{};
	};

	Point operator+(Point lhs, double numb);
	Point operator-(Point lhs, double numb);
	Point operator*(Point lhs, double numb);
	Point operator/(Point lhs, double numb);

} // _EVEASSETS_POINT_

#endif // _EVEASSETS_POINT_HPP_