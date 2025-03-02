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

#ifndef _EVEINDUSTRY_BLUEPRINTROJECT_HPP_
#define _EVEINDUSTRY_BLUEPRINTROJECT_HPP_

#include <vector>
#include <cassert>
#include <string>
#include <format>
#include <utility>
#include <unordered_map>
#include <numeric>
#include <algorithm>

#include "BlueprintRecord.hpp"
#include "SolarSystemRecord.hpp"

#include "Assets.hpp"
#include "Blueprint.hpp"
#include "Type.hpp"
#include "Group.hpp"
#include "SolarSystem.hpp"
#include "Logger.hpp"

namespace EVE::Industry
{

	struct BlueprintProject
	{
		using ME = EVE::Assets::BlueprintMaterialEfficiency;

		BlueprintProject(const BlueprintRecord& bp, const SolarSystemRecord& solSystem, ME me, const std::uint64_t maxRunsPerJob = 0);
		BlueprintProject(BlueprintRecord&& bp, SolarSystemRecord&& solSystem, ME me, const std::uint64_t maxRunsPerJob = 0);

		std::uint32_t id() const;
		void setSolarSystem(const SolarSystemRecord& solSystem);

		BlueprintRecord m_Blueprint;
		SolarSystemRecord m_SolarSystem;
		ME m_ME{};
		std::uint64_t m_MaxRunsPerJob{};

	private:
		void check();
	};

	struct BlueprintProjectSortByWeightName
	{
		bool operator()(const BlueprintProject& lhs, const BlueprintProject& rhs) const
		{
			if (lhs.m_Blueprint.weight() == rhs.m_Blueprint.weight())
			{
				return lhs.m_Blueprint.name() < rhs.m_Blueprint.name();
			}

			return lhs.m_Blueprint.weight() < rhs.m_Blueprint.weight();
		}
	};

	inline std::uint64_t getMaximumRunsPerJob(const std::vector<BlueprintProject>& src, const std::uint32_t bpid)
	{
		auto ittr = std::find_if(std::begin(src), std::end(src),
			[&bpid](const BlueprintProject& elem)
			{
				return elem.m_Blueprint.id() == bpid;
			}
		);

		return (ittr != std::end(src)) ? ittr->m_MaxRunsPerJob : 1;
	}

	inline const BlueprintProject* getBlueprintProjectFromBpID(const std::vector<BlueprintProject>& src, const std::uint32_t bpid)
	{
		auto ittr = std::find_if(std::begin(src), std::end(src),
			[&bpid](const BlueprintProject& elem)
			{
				return elem.m_Blueprint.id() == bpid;
			}
		);

		if (ittr == std::end(src))
		{
			return nullptr;
		}

		return &(*ittr);
	}

	inline const BlueprintProject* getBlueprintProjectFromIndustryType(const std::vector<BlueprintProject>& src, const std::uint32_t id)
	{
		auto ittr = std::find_if(std::begin(src), std::end(src),
			[&id](const BlueprintProject& elem)
			{
				return elem.m_Blueprint.producedID() == id;
			}
		);

		if (ittr == std::end(src))
		{
			return nullptr;
		}

		return &(*ittr);
	}

} // EVE::Industry

#endif // _EVEINDUSTRY_BLUEPRINTROJECT_HPP_