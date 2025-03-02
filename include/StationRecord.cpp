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

#include "StationRecord.hpp"

EVE::Industry::StationRecord::StationRecord(const std::uint32_t id)
	: BaseRecord()
{
	const Assets& assets = Assets::Instance();

	auto [sfound, station] = assets.m_StationsContainer.element(id);
	if (!sfound)
	{
		throw std::runtime_error(std::format("couldn't find station: {}", id));
	}

	this->m_ID = id;
	this->m_Name = station->m_Name;

	setValues(station);
}

EVE::Industry::StationRecord::StationRecord(Station station)
	: BaseRecord(station->m_Name, station->m_ID)
{
	setValues(station);
}

void EVE::Industry::StationRecord::setValues(Station station)
{
	this->m_RegionID = station->m_RegionID;
	this->m_SolarSystemID = station->m_SolarSystemID;
}
