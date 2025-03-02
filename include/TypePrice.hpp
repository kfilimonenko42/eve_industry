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

#ifndef _EVEINDUSTRY_TYPEPRICE_HPP_
#define _EVEINDUSTRY_TYPEPRICE_HPP_

#include <cstdint>
#include <chrono>

namespace EVE::Industry
{

	class TypePrice
	{
	public:
		using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;

		explicit TypePrice() = default;
		TypePrice(double sell, double buy);

	public:
		double m_PriceSell{};
		double m_PriceBuy{};
		time_point m_LastUpdateTime{};
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_TYPEPRICE_HPP_