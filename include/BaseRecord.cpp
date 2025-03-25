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

wxString EVE::Industry::BaseRecord::wxName() const
{
	return wxString::FromUTF8(this->m_Name);
}

std::uint32_t EVE::Industry::BaseRecord::id() const
{
	return this->m_ID;
}

std::string EVE::Industry::BaseRecord::toString() const
{
	return std::format("{} (id: {})", this->m_Name, this->m_ID);
}

wxString EVE::Industry::BaseRecord::towxString() const
{
	return wxString::FromUTF8(std::format("{} (id: {})", this->m_Name, this->m_ID));
}

