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

#include "MaterialBase.hpp"

EVE::Industry::MaterialBase::MaterialBase(const TypeRecord& type, const std::uint64_t quantity)
	: m_Type{ type }
{
	m_Type.setQuantity(quantity);
}

EVE::Industry::MaterialBase::MaterialBase(TypeRecord&& type, const std::uint64_t quantity)
	: m_Type{ std::move(type) }
{
	m_Type.setQuantity(quantity);
}

std::uint32_t EVE::Industry::MaterialBase::id() const
{
	return m_Type.id();
}
