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

#include "Blueprint.hpp"

std::uint32_t EVE::Assets::Blueprint::productID() const
{
	if (m_ManufacturingProducts.size() > 0)
	{
		return m_ManufacturingProducts[0].type_id();
	}

	return 0;
}

std::uint64_t EVE::Assets::Blueprint::runs(const std::uint64_t quantity) const
{
	const std::uint64_t _count = quantityManufacturedProduct();
	if (_count > 0)
	{
		return (std::uint64_t)std::ceil((double)quantity / (double)_count);
	}
	else
	{
		return 0;
	}
}

std::uint64_t EVE::Assets::Blueprint::quantityManufacturedProduct() const
{
	if (this->m_ManufacturingProducts.size() > 0)
	{
		return this->m_ManufacturingProducts[0].quantity();
	}

	return 0;
}

std::uint64_t EVE::Assets::Blueprint::quantityManufacturedMaterials(const std::uint64_t type_id) const
{
	auto ittr = std::find_if(
		std::begin(m_ManufacturingMaterials),
		std::end(m_ManufacturingMaterials),
		[type_id](const Material& material)
		{
			return material.type_id() == type_id;
		});

	if (ittr == std::end(m_ManufacturingMaterials))
	{
		return 0;
	}

	return ittr->quantity();
}