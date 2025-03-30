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

#include "BaseRecord.hpp"

EVE::Industry::BaseRecord::BaseRecord(const std::string& name, const std::uint32_t id)
	: m_Name{ name }, m_ID{ id }
{
}

EVE::Industry::BaseRecord::BaseRecord(std::string&& name, const std::uint32_t id)
	: m_Name{ std::move(name) }, m_ID{ id }
{
}

const std::string& EVE::Industry::BaseRecord::name() const
{
	return this->m_Name;
}

wxString EVE::Industry::BaseRecord::wxName() const
{
	return wxString::FromUTF8(this->m_Name);
}

std::uint32_t EVE::Industry::BaseRecord::id() const
{
	return this->m_ID;
}

std::string EVE::Industry::BaseRecord::toString() const
{
	return std::format("{} (id: {})", this->m_Name, this->m_ID);
}

wxString EVE::Industry::BaseRecord::towxString() const
{
	return wxString::FromUTF8(std::format("{} (id: {})", this->m_Name, this->m_ID));
}

