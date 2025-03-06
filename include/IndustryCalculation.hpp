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

#ifndef _EVEINDUSTRY_INDUSTRYCALCULATION_HPP_
#define _EVEINDUSTRY_INDUSTRYCALCULATION_HPP_

#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <memory>
#include <unordered_map>
#include <set>
#include <ranges>
#include <numeric>

#include "Material.hpp"
#include "IndustryProject.hpp"
#include "MaterialBase.hpp"

namespace EVE::Industry
{

	class IndustryCalculation
	{
	public:
		class IndustryElement
		{
		public:
			IndustryElement(
				TypeRecord&& type,
				BlueprintRecord&& blueprint,
				const std::uint64_t quantity,
				const std::uint64_t stock,
				const std::uint64_t maxRunsPerJob,
				const double secStatus,
				const EVE::Assets::BlueprintMaterialEfficiency bpME);
			~IndustryElement() = default;

			IndustryElement(const IndustryElement&) = delete;
			IndustryElement& operator=(const IndustryElement&) = delete;
			IndustryElement(IndustryElement&&) = delete;
			IndustryElement& operator=(IndustryElement&&) = delete;

			const TypeRecord& type() const;
			const BlueprintRecord& blueprint() const;
			bool isRaw() const;
			void addManufacturingElement(std::shared_ptr<IndustryElement> e);
			void addParentElement(std::shared_ptr<IndustryElement> e);
			void updateQuantity();
			void updateStages();
			void setNeedUpdate();
			bool getNeedUpdate() const;
			void updateWeight();
			std::uint64_t getWeight() const;
			bool hasParents() const;
			const std::vector<std::shared_ptr<IndustryElement>>& getParents() const;
			std::uint64_t quantity() const;
			std::uint64_t quantityManufacturedMaterials(std::uint64_t type_id) const;
			void clear();
			const std::vector<std::uint64_t>& getStages() const;

		private:
			std::vector<std::shared_ptr<IndustryElement>> m_ManufacturingElements;
			std::vector<std::shared_ptr<IndustryElement>> m_ParentElements;
			std::vector<std::uint64_t> m_Stages;
			std::uint64_t m_Quantity{};
			std::uint64_t m_Stock{};
			std::uint64_t m_StockAfterCalculation{};
			std::uint64_t m_ProducedStock{};
			std::uint64_t m_MaxRunsPerJob{};
			std::uint64_t m_Weight{};
			TypeRecord m_Type;
			BlueprintRecord m_Blueprint;
			double m_SecStatus{};
			EVE::Assets::BlueprintMaterialEfficiency m_BpME{};
			bool m_IsRaw{};
			bool m_NeedUpdate{};
		};

		IndustryCalculation(const IndustryProject& project, const bool fullCalculation = true);
		~IndustryCalculation();

		IndustryCalculation(const IndustryCalculation&) = delete;
		IndustryCalculation& operator=(const IndustryCalculation&) = delete;
		IndustryCalculation(IndustryCalculation&&) = delete;
		IndustryCalculation& operator=(IndustryCalculation&&) = delete;

		void clear();
		void getRawMaterials(std::vector<MaterialBase>& raw);
		void getBpsMaterials(std::vector<MaterialBlueprint>& types);
		void getAllMaterials(std::vector<MaterialProject>& materials);
		void getAllMaterialsNoIndustryMaterials(std::vector<MaterialProject>& materials);
		void getStages(std::vector<ProductionStage>& stages);

	private:
		void setIndustryElements(const IndustryProject& project);
		void calculate(const IndustryProject& project);
		void addIndustryElement(
			TypeRecord&& type,
			BlueprintRecord&& blueprint,
			const std::uint64_t quantity,
			const std::uint64_t stock,
			const std::uint64_t maxRunsPerJob,
			const double secStatus,
			const EVE::Assets::BlueprintMaterialEfficiency bpME,
			const bool needUpdate = false,
			std::shared_ptr<IndustryElement> parent = nullptr);
		void makeLinkParentChild(std::shared_ptr<IndustryElement> parent, std::shared_ptr<IndustryElement> child);
		void updateWeights();
		void updateStages();

	private:
		std::queue<std::shared_ptr<IndustryElement>> m_FillQueue;
		std::vector<std::shared_ptr<IndustryElement>> m_IndustryElements;
		bool m_FullCalculation{};
	};

}; // namespace EVE::Industry

#endif // _EVEINDUSTRY_INDUSTRYCALCULATION_HPP_