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

#ifndef _EVEINDUSTRY_STAGESTATUS_HPP_
#define _EVEINDUSTRY_STAGESTATUS_HPP_

#include <vector>
#include <string>
#include <utility>
#include <numeric>
#include <algorithm>

namespace EVE::Industry
{

	enum class StageStatus
	{
		Outstanding,
		InProgress,
		Finished
	};

	static const std::pair<StageStatus, std::string> arrStageStatus[] = {
		{ StageStatus::Outstanding, "Outstanding" },
		{ StageStatus::InProgress, "In Progress" },
		{ StageStatus::Finished, "Finished" },
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_STAGESTATUS_HPP_