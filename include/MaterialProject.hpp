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

#ifndef _EVEINDUSTRY_MATERIALPROJECT_HPP_
#define _EVEINDUSTRY_MATERIALPROJECT_HPP_

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

	struct MaterialProject
	{
		MaterialProject(const TypeRecord& type, const std::uint64_t quantity);
		MaterialProject(TypeRecord&& type, const std::uint64_t quantity);
		
		std::uint32_t id() const;
		void add(const std::uint64_t q_add);

		TypeRecord m_Type;
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_MATERIALPROJECT_HPP_