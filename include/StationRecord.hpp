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

#ifndef _EVEINDUSTRY_STATIONRECORD_HPP_
#define _EVEINDUSTRY_STATIONRECORD_HPP_

#include <string>
#include <format>
#include <cstdint>
#include <stdexcept>

#include "Assets.hpp"
#include "Station.hpp"
#include "BaseRecord.hpp"

namespace EVE::Industry
{

	class StationRecord : public BaseRecord
	{
	public:
		using Station = const EVE::Assets::Station*;

		StationRecord() = default;
		StationRecord(const std::uint32_t id);
		StationRecord(Station station);
		~StationRecord() override = default;

	private:
		void setValues(Station station);

	private:
		std::uint32_t m_RegionID{};
		std::uint32_t m_SolarSystemID{};
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_STATIONRECORD_HPP_