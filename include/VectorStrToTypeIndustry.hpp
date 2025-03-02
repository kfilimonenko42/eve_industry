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

#ifndef _EVEINDUSTRY_VECTORSTRTOTYPEINDUSTRY_HPP_
#define _EVEINDUSTRY_VECTORSTRTOTYPEINDUSTRY_HPP_

#include <vector>
#include <string>
#include <cassert>
#include <wx/wx.h>

#include "Material.hpp"
#include "MaterialProject.hpp"

namespace EVE::Industry
{

	struct VectorStrToTypeIndustry
	{
		void operator()(
			const std::vector<std::string>& source,
			std::unordered_map<std::uint32_t, std::uint64_t>& _dst);

		void operator()(
			const std::vector<std::string>& source,
			std::vector<EVE::Assets::Material>& _dst);

		void operator()(
			const std::vector<std::string>& source,
			std::vector<MaterialProject>& _dst);
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_VECTORSTRTOTYPEINDUSTRY_HPP_