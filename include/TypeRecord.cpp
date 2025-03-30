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

#include "TypeRecord.hpp"

EVE::Industry::TypeRecord::TypeRecord(const std::uint32_t id)
	: BaseRecord(), TradeRecord()
{
	const Assets& assets = Assets::Instance();

	auto [tfound, type] = assets.m_TypesContainer.element(id);
	if (!tfound)
	{
		throw std::runtime_error(std::format("couldn't find type: {}", id));
	}

	this->m_ID = id;
	this->m_Name = type->m_Name;

	setValues(type);
}

EVE::Industry::TypeRecord::TypeRecord(Type type)
	: BaseRecord(type->m_Name, type->m_ID)
{
	setValues(type);
}

const EVE::Industry::BaseRecord& EVE::Industry::TypeRecord::group() const
{
	return this->m_Group;
}

std::uint32_t EVE::Industry::TypeRecord::bpID() const
{
	return this->m_BlueprintID;
}

const std::string& EVE::Industry::TypeRecord::description() const
{
	return this->m_Description;
}

void EVE::Industry::TypeRecord::setValues(Type type)
{
	setVolume(type->m_PackagedVolume);
	this->m_BlueprintID = type->m_BlueprintID;
	this->m_Description = type->m_Description;

	const Assets& assets = Assets::Instance();

	const std::uint32_t group_id = type->m_GroupID;
	auto [gfound, group] = assets.m_GroupsContainer.element(group_id);
	if (!gfound)
	{
		throw std::runtime_error(std::format("couldn't find group: {}", group_id));
	}
	this->m_Group = BaseRecord(group->m_Name, group_id);
}
