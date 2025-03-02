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

#include "Point.hpp"

EVE::Assets::Point::Point(double _x, double _y, double _z)
	: m_X{ _x }, m_Y{ _y }, m_Z{ _z }
{
}

EVE::Assets::Point& EVE::Assets::Point::operator+=(double numb)
{
	this->m_X += numb;
	this->m_Y += numb;
	this->m_Z += numb;

	return *this;
}

EVE::Assets::Point& EVE::Assets::Point::operator-=(double numb)
{
	this->m_X -= numb;
	this->m_Y -= numb;
	this->m_Z -= numb;

	return *this;
}

EVE::Assets::Point& EVE::Assets::Point::operator*=(double numb)
{
	this->m_X *= numb;
	this->m_Y *= numb;
	this->m_Z *= numb;

	return *this;
}

EVE::Assets::Point& EVE::Assets::Point::operator/=(double numb)
{
	this->m_X /= numb;
	this->m_Y /= numb;
	this->m_Z /= numb;

	return *this;
}

EVE::Assets::Point EVE::Assets::operator+(Point lhs, double numb)
{
	lhs += numb;
	return lhs;
}

EVE::Assets::Point EVE::Assets::operator-(Point lhs, double numb)
{
	lhs -= numb;
	return lhs;
}

EVE::Assets::Point EVE::Assets::operator*(Point lhs, double numb)
{
	lhs *= numb;
	return lhs;
}

EVE::Assets::Point EVE::Assets::operator/(Point lhs, double numb)
{
	lhs /= numb;
	return lhs;
}