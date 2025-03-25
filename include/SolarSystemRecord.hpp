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

#ifndef _EVEINDUSTRY_SOLARSYSTEMRECORD_HPP_
#define _EVEINDUSTRY_SOLARSYSTEMRECORD_HPP_

#include <string>
#include <format>
#include <cstdint>
#include <stdexcept>
#include <wx/string.h>

#include "Assets.hpp"
#include "SolarSystem.hpp"
#include "BaseRecord.hpp"

namespace EVE::Industry
{

	class SolarSystemRecord : public BaseRecord
	{
	public:
		using SolarSystem = const EVE::Assets::SolarSystem*;

		SolarSystemRecord() = default;
		SolarSystemRecord(const std::uint32_t id);
		SolarSystemRecord(SolarSystem solSystem);
		~SolarSystemRecord() override = default;

		std::string toString() const override;
		wxString towxString() const override;
		double security() const;
		double costIndex(const bool isReaction = false) const;
		std::string costIndexString(const bool isReaction = false) const;

	private:
		void setValues(SolarSystem solSystem);

	private:
		double m_Security{};
		double m_ManufacturingIndex{};
		double m_ReactionIndex{};
		std::uint32_t m_RegionID{};
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_SOLARSYSTEMRECORD_HPP_