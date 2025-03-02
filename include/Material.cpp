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

#include "Material.hpp"

EVE::Assets::Material::Material(std::uint32_t _id, std::uint64_t _quantity)
	: m_Quantity{ _quantity }, m_TypeID{ _id }
{
}

EVE::Assets::Material& EVE::Assets::Material::operator+=(std::uint64_t _q)
{
	//assert(this->m_Quantity < (UINT64_MAX - _q));
	if (this->m_Quantity < (UINT64_MAX - _q))
	{
		this->m_Quantity += _q;
	}
	
	return *this;
}

EVE::Assets::Material& EVE::Assets::Material::operator-=(std::uint64_t _q)
{
	//assert(this->m_Quantity >= _q);
	if (this->m_Quantity >= _q)
	{
		this->m_Quantity -= _q;
	}

	return *this;
}

std::uint32_t EVE::Assets::Material::type_id() const
{
	return this->m_TypeID;
}

std::uint64_t EVE::Assets::Material::quantity() const
{
	return this->m_Quantity;
}

EVE::Assets::Material EVE::Assets::operator+(Material lhs, std::uint64_t _q)
{
	lhs += _q;
	return lhs;
}

EVE::Assets::Material EVE::Assets::operator-(Material lhs, std::uint64_t _q)
{
	lhs -= _q;
	return lhs;
}