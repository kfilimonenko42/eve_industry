#include "BaseRecord.hpp"

EVE::Industry::BaseRecord::BaseRecord(const std::string& name, const std::uint32_t id)
	: m_Name{ name }, m_ID{ id }
{
}

EVE::Industry::BaseRecord::BaseRecord(std::string&& name, const std::uint32_t id)
	: m_Name{ std::move(name) }, m_ID{ id }
{
}

const std::string& EVE::Industry::BaseRecord::name() const
{
	return this->m_Name;
}

std::uint32_t EVE::Industry::BaseRecord::id() const
{
	return this->m_ID;
}

std::string EVE::Industry::BaseRecord::toString() const
{
	return std::format("{} (id: {})", this->m_Name, this->m_ID);
}

