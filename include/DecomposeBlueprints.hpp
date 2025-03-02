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

#ifndef _EVEINDUSTRY_DECOMPOSEBLUERPINTS_HPP_
#define _EVEINDUSTRY_DECOMPOSEBLUERPINTS_HPP_

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <cassert>

#include "TypeRecord.hpp"
#include "BlueprintRecord.hpp"
#include "BlueprintProject.hpp"

namespace EVE::Industry
{

	struct DecomposeBlueprint
	{
		void operator()(
			const BlueprintRecord& _source,
			std::vector<BlueprintProject>& _dst);
	};

	struct MaterialsToBlueprints
	{
		void operator()(
			const std::vector<std::uint32_t>& _source,
			std::vector<BlueprintProject>& _dst);
	};

}

#endif // _EVEINDUSTRY_DECOMPOSEBLUERPINTS_HPP_