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

#include "SolarSystemRecord.hpp"

EVE::Industry::SolarSystemRecord::SolarSystemRecord(const std::uint32_t id)
	: BaseRecord()
{
	const Assets& assets = Assets::Instance();

	auto [sfound, solSystem] = assets.m_SolarSystemsContainer.element(id);
	if (!sfound)
	{
		throw std::runtime_error(std::format("couldn't find solar system: {}", id));
	}

	this->m_ID = id;
	this->m_Name = solSystem->m_Name;

	setValues(solSystem);
}

EVE::Industry::SolarSystemRecord::SolarSystemRecord(SolarSystem solSystem)
	: BaseRecord(solSystem->m_Name, solSystem->m_ID)
{
	setValues(solSystem);
}

std::string EVE::Industry::SolarSystemRecord::toString() const
{
	if (this->m_ID == 0)
	{
		return std::string();
	}
	else
	{
		return std::format("{} (security: {:.1f}, id: {})", this->m_Name, this->m_Security, this->m_ID);
	}
}

wxString EVE::Industry::SolarSystemRecord::towxString() const
{
	if (this->m_ID == 0)
	{
		return wxString();
	}
	else
	{
		return wxString::FromUTF8(std::format("{} (security: {:.1f}, id: {})", this->m_Name, this->m_Security, this->m_ID));
	}
}

double EVE::Industry::SolarSystemRecord::security() const
{
	return this->m_Security;
}

double EVE::Industry::SolarSystemRecord::costIndex(const bool isReaction) const
{
	return (isReaction ? this->m_ReactionIndex : this->m_ManufacturingIndex);
}

std::string EVE::Industry::SolarSystemRecord::costIndexString(const bool isReaction) const
{
	const double index = 100 * costIndex(isReaction);
	return std::format("{:.2f}%", index);
}

void EVE::Industry::SolarSystemRecord::setValues(SolarSystem solSystem)
{
	this->m_Security = solSystem->m_Security;
	this->m_RegionID = solSystem->m_RegionID;

	const Assets& assets = Assets::Instance();
	auto [scifound, sci] = assets.m_SystemsCostIndicesContainer.element(this->m_ID);
	if (scifound)
	{
		this->m_ManufacturingIndex = sci->m_Manufacturing;
		this->m_ReactionIndex = sci->m_Reaction;
	}
}
