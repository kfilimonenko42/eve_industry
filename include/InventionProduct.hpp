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

#ifndef _EVEASSETS_INVENTIONPRODUCT_HPP_
#define _EVEASSETS_INVENTIONPRODUCT_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <vector>

namespace EVE::Assets
{

	class InventionProduct
	{
	public:
		InventionProduct() = default;
		InventionProduct(std::uint32_t _id, std::uint64_t _quantity, double _probability);

	public:
		std::uint64_t m_Quantity{};
		std::uint32_t m_BluperintID{};
		double m_Probability{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_INVENTIONPRODUCT_HPP_