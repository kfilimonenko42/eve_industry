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

#ifndef _EVEINDUSTRY_BLUEPRINTRECORD_HPP_
#define _EVEINDUSTRY_BLUEPRINTRECORD_HPP_

#include <vector>
#include <string>
#include <format>
#include <cstdint>
#include <stdexcept>

#include "Assets.hpp"
#include "Blueprint.hpp"
#include "Type.hpp"
#include "BaseRecord.hpp"

namespace EVE::Industry
{

	class BlueprintRecord : public BaseRecord
	{
	public:
		using Type = const EVE::Assets::Type*;
		using Blueprint = const EVE::Assets::Blueprint*;
		using BlueprintSettings = EVE::Assets::BlueprintSettings;
		using Material = EVE::Assets::Material;

		BlueprintRecord() = default;
		BlueprintRecord(const std::uint32_t id);
		BlueprintRecord(Blueprint bp, Type type);
		~BlueprintRecord() override = default;

		const BaseRecord& group() const;
		std::uint64_t runs(const std::uint64_t quantity) const;
		const std::vector<Material>& getManufacturingMaterials() const;
		std::vector<std::uint32_t> getIDsManufacturingMaterials() const;
		std::uint64_t quantityManufacturedMaterials(const std::uint64_t type_id) const;
		std::uint64_t quantityManufacturedProduct() const;
		std::uint64_t maxRunsPerJob() const;
		std::uint32_t producedID() const;
		bool isReaction() const;
		std::uint64_t weight() const;
		EVE::Assets::BlueprintME bpME() const;
		EVE::Assets::StructureME structME() const;
		EVE::Assets::RigME rigME() const;
		double structureRoleBonus() const;
		double facilityTax() const;

	private:
		void setValues(Blueprint bp, Type type);

	private:
		std::vector<Material> m_ManufacturingMaterials;
		BlueprintSettings m_BlueprintSettings;
		std::uint64_t m_QuantityManufacturedProduct{};
		std::uint32_t m_ProductID{};
		BaseRecord m_Group;
		bool m_IsReaction{};
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_BLUEPRINTRECORD_HPP_