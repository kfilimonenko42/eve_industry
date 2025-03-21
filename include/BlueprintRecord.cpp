#include "BlueprintRecord.hpp"

EVE::Industry::BlueprintRecord::BlueprintRecord(const std::uint32_t id)
	: BaseRecord()
{
	const Assets& assets = Assets::Instance();

	auto [tfound, type] = assets.m_TypesContainer.element(id);
	if (!tfound)
	{
		throw std::runtime_error(std::format("couldn't find type: {}", id));
	}
	auto [bfound, bp] = assets.m_BlueprintsContainer.element(id);
	if (!bfound)
	{
		throw std::runtime_error(std::format("couldn't find blueprint: {}", id));
	}

	this->m_ID = id;
	this->m_Name = type->m_Name;

	setValues(bp, type);
}

EVE::Industry::BlueprintRecord::BlueprintRecord(Blueprint bp, Type type)
	: BaseRecord(type->m_Name, bp->m_ID)
{
	setValues(bp, type);
}

void EVE::Industry::BlueprintRecord::setValues(Blueprint bp, Type type)
{
	this->m_ManufacturingMaterials = bp->m_ManufacturingMaterials;
	this->m_QuantityManufacturedProduct = bp->quantityManufacturedProduct();
	this->m_ProductID = bp->productID();
	this->m_IsReaction = bp->m_Reaction;

	const Assets& assets = Assets::Instance();

	const std::uint32_t group_id = type->m_GroupID;
	auto [gfound, group] = assets.m_GroupsContainer.element(group_id);
	if (!gfound)
	{
		throw std::runtime_error(std::format("couldn't find group: {}", group_id));
	}
	this->m_Group = BaseRecord(group->m_Name, group_id);

	auto [bsfound, bpsettings] = assets.m_BlueprintsSettingsContainer.element(this->m_ID);
	if (bsfound)
	{
		this->m_BlueprintSettings = *bpsettings;
	}
}

const EVE::Industry::BaseRecord& EVE::Industry::BlueprintRecord::group() const
{
	return this->m_Group;
}

std::uint64_t EVE::Industry::BlueprintRecord::runs(const std::uint64_t quantity) const
{
	if (this->m_QuantityManufacturedProduct > 0)
	{
		return (std::uint64_t)std::ceil((double)quantity / (double)this->m_QuantityManufacturedProduct);
	}
	else
	{
		return 0;
	}
}

const std::vector<EVE::Assets::Material>& EVE::Industry::BlueprintRecord::getManufacturingMaterials() const
{
	return this->m_ManufacturingMaterials;
}

std::vector<std::uint32_t> EVE::Industry::BlueprintRecord::getIDsManufacturingMaterials() const
{
	std::vector<std::uint32_t> result;
	result.reserve(this->m_ManufacturingMaterials.size());

	for (const auto& element : this->m_ManufacturingMaterials)
	{
		result.push_back(element.type_id());
	}

	std::sort(std::begin(result), std::end(result));
	result.erase(std::unique(std::begin(result), std::end(result)), std::end(result));

	return result;
}

std::uint64_t EVE::Industry::BlueprintRecord::quantityManufacturedMaterials(const std::uint64_t type_id) const
{
	auto ittr = std::find_if(
		std::begin(m_ManufacturingMaterials),
		std::end(m_ManufacturingMaterials),
		[type_id](const Material& material)
		{
			return material.type_id() == type_id;
		});

	if (ittr == std::end(m_ManufacturingMaterials))
	{
		return 0;
	}

	return ittr->quantity();
}

std::uint64_t EVE::Industry::BlueprintRecord::quantityManufacturedProduct() const
{
	return this->m_QuantityManufacturedProduct;
}

std::uint64_t EVE::Industry::BlueprintRecord::maxRunsPerJob() const
{
	if (this->m_BlueprintSettings.m_MaxRuns == 0)
	{
		return 1;
	}

	return this->m_BlueprintSettings.m_MaxRuns;
}

std::uint32_t EVE::Industry::BlueprintRecord::producedID() const
{
	return this->m_ProductID;
}

bool EVE::Industry::BlueprintRecord::isReaction() const
{
	return this->m_IsReaction;
}

std::uint64_t EVE::Industry::BlueprintRecord::weight() const
{
	return this->m_BlueprintSettings.m_Weight;
}

EVE::Assets::BlueprintME EVE::Industry::BlueprintRecord::bpME() const
{
	return this->m_BlueprintSettings.m_BpME;
}

EVE::Assets::StructureME EVE::Industry::BlueprintRecord::structME() const
{
	return this->m_BlueprintSettings.m_StructME;
}

EVE::Assets::RigME EVE::Industry::BlueprintRecord::rigME() const
{
	return this->m_BlueprintSettings.m_RigME;
}

double EVE::Industry::BlueprintRecord::structureRoleBonus() const
{
	return this->m_BlueprintSettings.m_StructureRoleBonus;
}

double EVE::Industry::BlueprintRecord::facilityTax() const
{
	return this->m_BlueprintSettings.m_FacilityTax;
}
