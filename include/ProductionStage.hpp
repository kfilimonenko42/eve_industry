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

#ifndef _EVEINDUSTRY_PRODUCTIONSTAGE_HPP_
#define _EVEINDUSTRY_PRODUCTIONSTAGE_HPP_

#include <vector>
#include <cassert>
#include <string>
#include <utility>
#include <unordered_map>
#include <numeric>
#include <algorithm>

#include "BlueprintRecord.hpp"
#include "StageStatus.hpp"

namespace EVE::Industry
{

	struct ProductionStage
	{
		ProductionStage(
			const std::uint32_t stage, const BlueprintRecord& blueprint,
			const std::uint64_t runs, const StageStatus status = StageStatus::Outstanding);
		ProductionStage(
			const std::uint32_t stage, BlueprintRecord&& blueprint,
			const std::uint64_t runs, const StageStatus status = StageStatus::Outstanding);

		bool operator==(const ProductionStage& rhs) const
		{
			return this->m_Stage == rhs.m_Stage;
		}

		auto operator<=>(const ProductionStage& rhs) const
		{
			return this->m_Stage <=> rhs.m_Stage;
		}

		std::uint32_t id() const;
		void setStatus(const StageStatus status);

		std::uint32_t m_Stage{};
		BlueprintRecord m_Blueprint;
		std::uint64_t m_Runs{};
		std::uint64_t m_Quantity{};
		StageStatus m_Status{ StageStatus::Outstanding };

	};

	struct MaterialsBaseSortByStageReversed
	{
		bool operator()(const ProductionStage& lhs, const ProductionStage& rhs) const
		{
			return !(lhs.m_Stage < rhs.m_Stage);
		}
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_PRODUCTIONSTAGE_HPP_