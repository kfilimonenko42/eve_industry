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

#include "IndustryProject.hpp"
#include "Assets.hpp"
#include "JsonIndustryLoader.hpp"
#include "JsonIndustrySaver.hpp"

EVE::Industry::IndustryProject::IndustryProject(const std::string& name)
	: m_Name{ name }
{
}

void EVE::Industry::IndustryProject::clear()
{
	m_TypesProject.clear();
	m_Stock.clear();
	m_BlueprintsList.clear();
	m_TypesBase.clear();
	m_TypesBlueprint.clear();
	m_ProductionStages.clear();
}

void EVE::Industry::IndustryProject::setName(std::string&& name)
{
	m_Name = std::move(name);
}

std::string EVE::Industry::IndustryProject::name()
{
	return m_Name;
}

const std::string& EVE::Industry::IndustryProject::name() const
{
	return m_Name;
}

bool EVE::Industry::IndustryProject::getModified() const
{
	return m_Modified;
}

void EVE::Industry::IndustryProject::setModified(bool flag)
{
	m_Modified = flag;
}

void EVE::Industry::IndustryProject::setFileName(const std::string& fileName)
{
	if (!fileName.empty())
	{
		m_FileName = fileName;
	}
}

const std::string& EVE::Industry::IndustryProject::fileName() const
{
	return m_FileName;
}

std::vector<std::uint32_t> EVE::Industry::IndustryProject::getTypeProjectIDs() const
{
	std::vector<std::uint32_t> _result;
	_result.reserve(_result.size());

	for (const auto& element : m_TypesProject.get())
	{
		_result.push_back(element.m_Type.id());
	}

	std::sort(std::begin(_result), std::end(_result));
	_result.erase(std::unique(std::begin(_result), std::end(_result)), std::end(_result));

	return _result;
}

std::uint64_t EVE::Industry::IndustryProject::getStock(const std::uint32_t type_id) const
{
	const auto& container = m_Stock.get();

	auto ittr = std::find_if(std::begin(container), std::end(container),
		[type_id](const MaterialProject& elem)
		{
			return elem.m_Type.id() == type_id;
		});

	if (ittr != std::end(container))
	{
		return ittr->m_Type.getQuantity();
	}

	return 0;
}
