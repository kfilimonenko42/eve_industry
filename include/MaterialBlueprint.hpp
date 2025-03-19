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

#ifndef _EVEINDUSTRY_MATERIALBLUEPRINTBASE_HPP_
#define _EVEINDUSTRY_MATERIALBLUEPRINTBASE_HPP_

#include <vector>
#include <cassert>
#include <string>
#include <utility>
#include <unordered_map>
#include <numeric>
#include <algorithm>

#include "TypeRecord.hpp"
#include "BlueprintRecord.hpp"
#include "EsiOrderSettings.hpp"

namespace EVE::Industry
{

	struct MaterialBlueprint
	{
		MaterialBlueprint(const BlueprintRecord& bp, const TypeRecord& type, const uint64_t quantity);
		MaterialBlueprint(BlueprintRecord&& bp, TypeRecord&& type, const uint64_t quantity);

		std::uint32_t id() const;

		BlueprintRecord m_Blueprint;
		TypeRecord m_Type;
		EsiOrderSettings m_EsiSettings;
		uint64_t m_Runs{};
	};

	struct MaterialsBlueprintSortByWeightName
	{
		bool operator()(const MaterialBlueprint& lhs, const MaterialBlueprint& rhs) const
		{
			if (lhs.m_Blueprint.weight() == rhs.m_Blueprint.weight())
			{
				return lhs.m_Blueprint.name() < rhs.m_Blueprint.name();
			}

			return lhs.m_Blueprint.weight() < rhs.m_Blueprint.weight();
		}
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_MATERIALBLUEPRINTBASE_HPP_