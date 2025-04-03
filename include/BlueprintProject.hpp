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

		template<typename BpRecord, typename SolRecord>
		BlueprintProject(BpRecord&& bp, SolRecord&& solSystem, ME me, 
			std::uint64_t maxRunsPerJob = 0, double structRoleBonus = 0.0, double facilityTax = 0.0);

		std::uint32_t id() const
		{
			return this->m_Blueprint.id();
		}

		void setSolarSystem(const SolarSystemRecord& solSystem)
		{
			this->m_SolarSystem = solSystem;
		}

		BlueprintRecord m_Blueprint;
		SolarSystemRecord m_SolarSystem;
		ME m_ME{};
		std::uint64_t m_MaxRunsPerJob{};
		double m_StructRoleBonus{};
		double m_FacilityTax{};

	private:
		void check()
		{
			if (this->m_MaxRunsPerJob <= 0)
			{
				this->m_MaxRunsPerJob = this->m_Blueprint.maxRunsPerJob();
			}

			if (this->m_StructRoleBonus <= 0)
			{
				this->m_StructRoleBonus = this->m_Blueprint.structureRoleBonus();
			}

			if (this->m_FacilityTax <= 0)
			{
				this->m_FacilityTax = this->m_Blueprint.facilityTax();
			}

			if (this->m_ME.m_BpME == EVE::Assets::BlueprintME::ME_0)
			{
				this->m_ME.m_BpME = this->m_Blueprint.bpME();
			}

			if (this->m_ME.m_StructME == EVE::Assets::StructureME::ME_0)
			{
				this->m_ME.m_StructME = this->m_Blueprint.structME();
			}

			if (this->m_ME.m_RigME == EVE::Assets::RigME::NO_RIG)
			{
				this->m_ME.m_RigME = this->m_Blueprint.rigME();
			}
		}
	};

	template<typename BpRecord, typename SolRecord>
	inline BlueprintProject::BlueprintProject(BpRecord&& bp, SolRecord&& solSystem, ME me,
		std::uint64_t maxRunsPerJob, double structRoleBonus, double facilityTax)
		: m_Blueprint{ std::forward<BpRecord>(bp) }, m_SolarSystem{ std::forward<SolRecord>(solSystem) }, m_ME{ me },
		m_MaxRunsPerJob{ maxRunsPerJob }, m_StructRoleBonus{ structRoleBonus }, m_FacilityTax{ facilityTax }
	{
		check();
	}

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
	
	inline std::size_t getBlueprintLineIndex(const std::vector<BlueprintProject>& src, const std::uint32_t bpid)
	{
		auto ittr = std::find_if(std::begin(src), std::end(src),
			[&bpid](const BlueprintProject& elem)
			{
				return elem.m_Blueprint.id() == bpid;
			}
		);

		if (ittr == std::end(src))
		{
			return -1;
		}

		return std::distance(std::begin(src), ittr);
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