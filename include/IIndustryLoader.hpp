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

#ifndef _EVEINDUSTRY_IINDUSTRYLOADER_HPP_
#define _EVEINDUSTRY_IINDUSTRYLOADER_HPP_

#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <utility>

#include "IndustryProject.hpp"

namespace EVE::Industry
{

	class IIndustryLoader
	{
	public:
		virtual ~IIndustryLoader() = default;

		virtual void load(const std::string& fileName, IndustryProject& dst) = 0;
	};

}

#endif // _EVEINDUSTRY_IINDUSTRYLOADER_HPP_