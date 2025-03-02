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

#ifndef _EVEINDUSTRY_INDUSTRYPROJECT_HPP_
#define _EVEINDUSTRY_INDUSTRYPROJECT_HPP_

#include <vector>
#include <cassert>
#include <string>
#include <utility>
#include <memory>
#include <unordered_map>

#include "Material.hpp"
#include "MaterialProject.hpp"
#include "BlueprintProject.hpp"
#include "MaterialBase.hpp"
#include "MaterialBlueprint.hpp"
#include "ProductionStage.hpp"
#include "ListDataWrapper.hpp"

namespace EVE::Industry
{

	class IndustryProject
	{
	public:
		using BpME = EVE::Assets::BlueprintMaterialEfficiency;

		IndustryProject() = default;
		explicit IndustryProject(const std::string& name);

		void clear();

		void setName(std::string&& name);
		std::string name();
		const std::string& name() const;
		bool getModified() const;
		void setModified(bool flag);
		void setFileName(const std::string& fileName);
		const std::string& fileName() const;

		std::vector<std::uint32_t> getTypeProjectIDs() const;
		void restoreME();
		void restoreSystems();
		void restoreMaxRunsPerJob();

		std::uint64_t getStock(const std::uint32_t type_id) const;

	public:
		//
		ListDataWrapper<MaterialProject> m_TypesProject;
		ListDataWrapper<MaterialProject> m_Stock;
		//
		ListDataWrapper<BlueprintProject> m_BlueprintsList;
		std::unordered_map<std::uint32_t, BpME> m_BPME;
		std::unordered_map<std::uint32_t, SolarSystemRecord> m_BPSystem;
		std::unordered_map<std::uint32_t, std::uint64_t> m_BPMaxRunsPreJob;
		//
		ListDataWrapper<MaterialBase> m_TypesBase;
		ListDataWrapper<MaterialBlueprint> m_TypesBlueprint;
		//
		ListDataWrapper<ProductionStage> m_ProductionStages;

	private:
		std::string m_Name;
		std::string m_FileName;
		bool m_Modified{};
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_INDUSTRYPROJECT_HPP_