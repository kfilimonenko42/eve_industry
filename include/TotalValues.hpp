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

#ifndef _EVEINDUSTRY_TOTALVALUES_HPP_
#define _EVEINDUSTRY_TOTALVALUES_HPP_

#include <vector>
#include <string>

#include "StageStatus.hpp"

namespace EVE::Industry
{

	template <typename T>
	inline double totalVolumePackaged(const std::vector<T>& source)
	{
		return std::accumulate(std::begin(source), std::end(source), 0.0,
			[](double summ, const T& element) -> double
			{
				return element.m_Type.getVolumeTotal() + summ;
			});
	}

	template <typename T>
	inline double totalPriceSell(const std::vector<T>& source)
	{
		return std::accumulate(std::begin(source), std::end(source), 0.0,
			[](double summ, const T& element) -> double
			{
				return element.m_Type.getPriceSellTotal() + summ;
			});
	}

	template <typename T>
	inline double totalPriceBuy(const std::vector<T>& source)
	{
		return std::accumulate(std::begin(source), std::end(source), 0.0,
			[](double summ, const T& element) -> double
			{
				return element.m_Type.getPriceBuyTotal() + summ;
			});
	}

	template <typename T>
	inline std::size_t totalStatuses(const std::vector<T>& source, const StageStatus status)
	{
		return std::count_if(std::begin(source), std::end(source),
			[status](const T& element) -> double
			{
				return element.m_Status == status;
			});
	}

}

#endif // _EVEINDUSTRY_TOTALVALUES_HPP_