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
#include "ProductionStage.hpp"
#include "BlueprintProject.hpp"
#include "IndustryProject.hpp"
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

	inline double jobCost(const ProductionStage& stage, const IndustryProject* project)
	{
		const auto& assets = Assets::Instance();

		const auto& bp = stage.m_Blueprint;
		const auto& list = bp.getManufacturingMaterials();
		const auto materialsTotalCost = stage.m_Runs * std::accumulate(std::begin(list), std::end(list), 0.0,
			[&assets](double summ, const EVE::Assets::Material& element) -> double
			{
				auto [mpfound, mp] = assets.m_MarketPricesContainer.element(element.type_id());
				return ((mpfound ? mp->m_Adjusted : 0) * element.quantity()) + summ;
			});

		const auto totalJobCost = materialsTotalCost * stage.m_SolarSystem.costIndex(stage.m_Blueprint.isReaction());

		double structRoleBonusIndex = bp.structureRoleBonus();
		double facilityTaxIndex = bp.facilityTax();
		if (project)
		{
			const auto bpProject = getBlueprintProjectFromBpID(project->m_BlueprintsList.get(), bp.id());
			if (bpProject)
			{
				structRoleBonusIndex = bpProject->m_StructRoleBonus;
				facilityTaxIndex = bpProject->m_FacilityTax;
			}
		}
		const auto facilityRoleBonus = totalJobCost * structRoleBonusIndex;
		const auto facilityTax = materialsTotalCost * facilityTaxIndex;
		const auto scc = materialsTotalCost * 0.04;

		return totalJobCost - facilityRoleBonus + facilityTax + scc;
	}

	template <typename T>
	inline double totalJobsCost(const std::vector<T>& source, const IndustryProject* project)
	{
		return std::accumulate(std::begin(source), std::end(source), 0.0,
			[project](double summ, const T& element) -> double
			{
				return jobCost(element, project) + summ;
			});
	}

}

#endif // _EVEINDUSTRY_TOTALVALUES_HPP_