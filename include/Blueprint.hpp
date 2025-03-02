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

#ifndef _EVEASSETS_BLUEPRINT_HPP_
#define _EVEASSETS_BLUEPRINT_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <algorithm>
#include <cmath>

#include "Material.hpp"
#include "InventionProduct.hpp"
#include "BlueprintMaterialEfficiency.hpp"

namespace EVE::Assets
{

	class Blueprint
	{
	public:
		Blueprint() = default;

		std::uint32_t productID() const;
		std::uint64_t runs(const std::uint64_t quantity) const;
		std::uint64_t quantityManufacturedProduct() const;
		std::uint64_t quantityManufacturedMaterials(const std::uint64_t type_id) const;

		bool operator==(const Blueprint& rhs) const
		{
			return this->m_ID == rhs.m_ID;
		}

		auto operator<=>(const Blueprint& rhs) const
		{
			return this->m_ID <=> rhs.m_ID;
		}

	public:
		std::vector<Material> m_ManufacturingMaterials;
		std::vector<Material> m_ManufacturingProducts;
		std::vector<Material> m_InventionMaterials;
		std::vector<Material> m_ResearchMeMaterials;
		std::vector<Material> m_ResearchPeMaterials;
		std::vector<InventionProduct> m_InventionProducts;
		std::uint32_t m_ID{};
		std::uint32_t m_TypeID{};
		std::uint32_t m_ProductionLimit{};
		std::uint32_t m_ManufacturingTime{};
		std::uint32_t m_CopyingTime{};
		std::uint32_t m_InventionTime{};
		std::uint32_t m_ResearchMeTime{};
		std::uint32_t m_ResearchPeTime{};
		std::uint32_t m_MarketGroupId{};
		bool m_Reaction{};
	};

	[[nodiscard]] constexpr std::vector<std::uint32_t> getTypeIDsFromListMaterials(const std::vector<EVE::Assets::Material>& _list)
	{
		std::vector<std::uint32_t> result;
		result.reserve(_list.size());

		for (const auto& element : _list)
		{
			result.push_back(element.type_id());
		}

		std::sort(std::begin(result), std::end(result));
		result.erase(std::unique(std::begin(result), std::end(result)), std::end(result));

		return result;
	}

} // namespace EVE::Assets

#endif // _EVEASSETS_BLUEPRINT_HPP_