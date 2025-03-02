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

#ifndef _EVEASSETS_BLUEPRINTMATERIALEFFICIENCY_HPP_
#define _EVEASSETS_BLUEPRINTMATERIALEFFICIENCY_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <algorithm>
#include <cmath>

namespace EVE::Assets
{

	static constexpr std::uint32_t SecondsIn30Days = 2592000;

	enum class BlueprintME
	{
		ME_0,
		ME_1,
		ME_2,
		ME_3,
		ME_4,
		ME_5,
		ME_6,
		ME_7,
		ME_8,
		ME_9,
		ME_10
	};

	static const std::pair<BlueprintME, std::string> arrBlueprintME[] = {
		{ BlueprintME::ME_0, "0%" },
		{ BlueprintME::ME_1, "1%" },
		{ BlueprintME::ME_2, "2%" },
		{ BlueprintME::ME_3, "3%" },
		{ BlueprintME::ME_4, "4%" },
		{ BlueprintME::ME_5, "5%" },
		{ BlueprintME::ME_6, "6%" },
		{ BlueprintME::ME_7, "7%" },
		{ BlueprintME::ME_8, "8%" },
		{ BlueprintME::ME_9, "9%" },
		{ BlueprintME::ME_10, "10%" }
	};

	enum class StructureME
	{
		ME_0,
		ME_1
	};

	static const std::pair<StructureME, std::string> arrStructureME[] = {
		{ StructureME::ME_0, "0%" },
		{ StructureME::ME_1, "1%" }
	};

	enum class RigME
	{
		NO_RIG,
		T1,
		T2
	};

	static const std::pair<RigME, std::string> arrRigME[] = {
		{ RigME::NO_RIG, "NO RIG" },
		{ RigME::T1, "T1" },
		{ RigME::T2, "T2" }
	};

	[[nodiscard]] constexpr double me(const BlueprintME me)
	{
		switch (me)
		{
		case BlueprintME::ME_1:
			return 0.01;
		case BlueprintME::ME_2:
			return 0.02;
		case BlueprintME::ME_3:
			return 0.03;
		case BlueprintME::ME_4:
			return 0.04;
		case BlueprintME::ME_5:
			return 0.05;
		case BlueprintME::ME_6:
			return 0.06;
		case BlueprintME::ME_7:
			return 0.07;
		case BlueprintME::ME_8:
			return 0.08;
		case BlueprintME::ME_9:
			return 0.09;
		case BlueprintME::ME_10:
			return 0.1;
		default:
			return 0.0;
		}
	}

	[[nodiscard]] constexpr double me(const StructureME me)
	{
		switch (me)
		{
		case StructureME::ME_0:
			return 0.0;
		case StructureME::ME_1:
			return 0.01;
		default:
			return 0.0;
		}
	}

	[[nodiscard]] constexpr double me(
		const double security,
		const bool isReaction,
		const RigME me)
	{
		double bonus = isReaction ? 0.0 : 1.0;
		if (security >= 0.1 && security < 0.5)
		{
			bonus = isReaction ? 1.0 : 1.9;
		}
		else if (security <= 0.0 && security >= -1.0)
		{
			bonus = isReaction ? 1.1 : 2.1;
		}

		switch (me)
		{
		case RigME::T1:
			return (2 * bonus) / 100;
		case RigME::T2:
			return (2.40 * bonus) / 100;
		default:
			return 0.0;
		}
	}

	struct BlueprintMaterialEfficiency
	{
		BlueprintME m_BpME{ BlueprintME::ME_0 };
		StructureME m_StructME{ StructureME::ME_0 };
		RigME m_RigME{ RigME::NO_RIG };

		BlueprintMaterialEfficiency() = default;
		BlueprintMaterialEfficiency(BlueprintME bpME, StructureME structME, RigME rigME)
			: m_BpME{ bpME }, m_StructME{ structME }, m_RigME{ rigME }
		{
		}
	};

	[[nodiscard]] inline const BlueprintMaterialEfficiency getBlueprintMaterialEfficiency(
		const std::uint32_t id,
		const auto& container)
	{
		if (container.contains(id))
		{
			return container.at(id);
		}

		return {};
	}

} // namespace EVE::Assets

#endif // _EVEASSETS_BLUEPRINTMATERIALEFFICIENCY_HPP_