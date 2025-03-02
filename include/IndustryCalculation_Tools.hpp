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

#ifndef _EVEINDUSTRY_INDUSTRYCALCULATION_HELPER_HPP_
#define _EVEINDUSTRY_INDUSTRYCALCULATION_HELPER_HPP_

#include <cstdint>
#include <cassert>
#include <cmath>

#include "Blueprint.hpp"
#include "Logger.hpp"

namespace EVE::Industry
{
	[[nodiscard]] inline std::uint64_t quantity(
		const std::uint64_t _runs, const std::uint64_t _quantity1run, const bool isReaction, const double secStatus,
		const EVE::Assets::BlueprintME _bpme, const EVE::Assets::StructureME _structME, const EVE::Assets::RigME _rig)
	{
		if (isReaction)
		{
			if (secStatus >= 0.5)
			{
				Log::LOG_INFO("Reactions available only in < 0.5 systems");
				return 0;
			}

			const double d_rig = (1.0 - EVE::Assets::me(secStatus, true, _rig));

			const std::uint64_t count =
				(std::uint64_t)std::ceil(_quantity1run *
					_runs *
					d_rig);

			return std::max(_runs, count);
		}
		else
		{
			const double d_bp = (1.0 - EVE::Assets::me(_bpme));
			const double d_struct = (1.0 - EVE::Assets::me(_structME));
			const double d_rig = (1.0 - EVE::Assets::me(secStatus, false, _rig));

			const std::uint64_t count =
				(std::uint64_t)std::ceil(_quantity1run *
					d_bp *
					_runs *
					d_struct *
					d_rig);

			return std::max(_runs, count);
		}
	}

	inline std::uint64_t useStock(std::uint64_t& _count, std::uint64_t& _stock)
	{
		if (_stock > 0 && _count > 0)
		{
			if (_stock >= _count)
			{
				const std::uint64_t tmp = _count;

				_stock -= _count;
				_count = 0;

				return tmp;
			}
			else
			{
				const std::uint64_t tmp = _stock;

				_count -= _stock;
				_stock = 0;

				return tmp;
			}
		}

		return 0;
	}
}

#endif // _EVEINDUSTRY_INDUSTRYCALCULATION_HELPER_HPP_