#include "TypeRecord.hpp"

EVE::Industry::TypeRecord::TypeRecord(const std::uint32_t id)
	: BaseRecord(), TradeRecord()
{
	const Assets& assets = Assets::Instance();

	auto [tfound, type] = assets.m_TypesContainer.element(id);
	if (!tfound)
	{
		throw std::runtime_error(std::format("couldn't find type: {}", id));
	}

	this->m_ID = id;
	this->m_Name = type->m_Name;

	setValues(type);
}

EVE::Industry::TypeRecord::TypeRecord(Type type)
	: BaseRecord(type->m_Name, type->m_ID)
{
	setValues(type);
}

const EVE::Industry::BaseRecord& EVE::Industry::TypeRecord::group() const
{
	return this->m_Group;
}

std::uint32_t EVE::Industry::TypeRecord::bpID() const
{
	return this->m_BlueprintID;
}

const std::string& EVE::Industry::TypeRecord::description() const
{
	return this->m_Description;
}

void EVE::Industry::TypeRecord::setValues(Type type)
{
	setVolume(type->m_PackagedVolume);
	this->m_BlueprintID = type->m_BlueprintID;
	this->m_Description = type->m_Description;

	const Assets& assets = Assets::Instance();

	const std::uint32_t group_id = type->m_GroupID;
	auto [gfound, group] = assets.m_GroupsContainer.element(group_id);
	if (!gfound)
	{
		throw std::runtime_error(std::format("couldn't find group: {}", group_id));
	}
	this->m_Group = BaseRecord(group->m_Name, group_id);
}
