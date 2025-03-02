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

#ifndef _EVEINDUSTRY_MATERIALBASE_HPP_
#define _EVEINDUSTRY_MATERIALBASE_HPP_

#include <vector>
#include <cassert>
#include <string>
#include <utility>
#include <unordered_map>
#include <numeric>
#include <algorithm>

#include "TypeRecord.hpp"

namespace EVE::Industry
{

	struct MaterialBase
	{
		MaterialBase(const TypeRecord& type, const std::uint64_t quantity);
		MaterialBase(TypeRecord&& type, const std::uint64_t quantity);

		std::uint32_t id() const;
		TypeRecord m_Type;
	};

	struct MaterialsBaseSortByGroupTypeIds
	{
		bool operator()(const MaterialBase& lhs, const MaterialBase& rhs) const
		{
			if (lhs.m_Type.group().id() == rhs.m_Type.group().id())
			{
				return lhs.m_Type.id() < rhs.m_Type.id();
			}

			return lhs.m_Type.group().id() < rhs.m_Type.group().id();
		}
	};

	struct MaterialsBaseSortByGroupIdTypeName
	{
		bool operator()(const MaterialBase& lhs, const MaterialBase& rhs) const
		{
			if (lhs.m_Type.group().id() == rhs.m_Type.group().id())
			{
				return lhs.m_Type.name() < rhs.m_Type.name();
			}

			return lhs.m_Type.group().id() < rhs.m_Type.group().id();
		}
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_MATERIALBASE_HPP_