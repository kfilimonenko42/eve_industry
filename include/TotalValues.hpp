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
#include <cstdint>

#include "StageStatus.hpp"
#include "AppraisalContainer.hpp"
#include "BlueprintRecord.hpp"
#include "SolarSystemRecord.hpp"
#include "Assets.hpp"

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
				return priceSell(UpdatePriceRecord{ 0, element.id(), element.m_EsiSettings }, element.m_Type.getQuantity()) + summ;
			});
	}

	template <typename T>
	inline double totalPriceBuy(const std::vector<T>& source)
	{
		return std::accumulate(std::begin(source), std::end(source), 0.0,
			[](double summ, const T& element) -> double
			{
				return priceBuy(UpdatePriceRecord{ 0, element.id(), element.m_EsiSettings }, element.m_Type.getQuantity()) + summ;
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

	inline double jobCost(const BlueprintRecord& bp, const SolarSystemRecord& solSystem, const std::uint64_t runs)
	{
		const auto& assets = Assets::Instance();

		const auto& list = bp.getManufacturingMaterials();
		const auto materialsTotalCost = runs * std::accumulate(std::begin(list), std::end(list), 0.0,
			[&assets](double summ, const EVE::Assets::Material& element) -> double
			{
				auto [mpfound, mp] = assets.m_MarketPricesContainer.element(element.type_id());
				return ((mpfound ? mp->m_Adjusted : 0) * element.quantity()) + summ;
			});

		const auto totalJobCost = materialsTotalCost * solSystem.costIndex(bp.isReaction());
		const auto facilityRoleBonus = totalJobCost * bp.structureRoleBonus();
		const auto facilityTax = materialsTotalCost * bp.facilityTax();
		const auto scc = materialsTotalCost * 0.04;

		return totalJobCost - facilityRoleBonus + facilityTax + scc;
	}

	template <typename T>
	inline double totalJobsCost(const std::vector<T>& source)
	{
		return std::accumulate(std::begin(source), std::end(source), 0.0,
			[](double summ, const T& element) -> double
			{
				return jobCost(element.m_Blueprint, element.m_SolarSystem, element.m_Runs) + summ;
			});
	}

}

#endif // _EVEINDUSTRY_TOTALVALUES_HPP_