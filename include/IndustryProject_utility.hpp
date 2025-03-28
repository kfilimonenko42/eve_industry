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

#ifndef _EVEINDUSTRY_INDUSTRYPROJECTUTILITY_HPP_
#define _EVEINDUSTRY_INDUSTRYPROJECTUTILITY_HPP_

#include <string>
#include <format>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>
#include <filesystem>
#include <wx/wx.h>

#include "IndustryProject.hpp"
#include "DecomposeBlueprints.hpp"
#include "WxTextToVectorStr.hpp"
#include "IndustryCalculation.hpp"
#include "JsonIndustrySaver.hpp"
#include "JsonIndustryLoader.hpp"
#include "VectorStrToTypeIndustry.hpp"
#include "FormAddTypesText.hpp"
#include "BlueprintMaterialEfficiency.hpp"
#include "FormMaterialsStages.hpp"

namespace EVE::Industry
{

	struct LoadProject
	{
		LoadProject(wxWindow* parent)
			: m_Parent{ parent }
		{
		}

		bool operator()(IndustryProject& project)
		{
			wxFileDialog opendialog(m_Parent, "open eve indistry project", "", "", "ei files (*.ei)|*.ei", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
			opendialog.SetDirectory(std::format("{}/saves", std::filesystem::current_path().string()));

			if (opendialog.ShowModal() != wxID_OK)
			{
				return false;
			}

			const std::string fileName = opendialog.GetPath().ToStdString();
			std::unique_ptr<IIndustryLoader> loader = std::make_unique<JsonIndustryLoader>();
			loader->load(
				fileName,
				project);

			project.setFileName(fileName);

			return true;
		}

	private:
		wxWindow* m_Parent{};
	};

	struct SaveProjectAs
	{
		SaveProjectAs(wxWindow* parent)
			: m_Parent{ parent }
		{
		}

		bool operator()(IndustryProject& project)
		{
			wxFileDialog savedialog(m_Parent, "save eve indistry project", "", "", "ei files (*.ei)|*.ei", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
			savedialog.SetDirectory(std::format("{}/saves", std::filesystem::current_path().string()));

			if (savedialog.ShowModal() != wxID_OK)
			{
				return false;
			}

			const std::string fileName = savedialog.GetPath().ToStdString();
			std::unique_ptr<IIndastrySaver> saver = std::make_unique<JsonIndustrySaver>();
			saver->save(
				fileName,
				project);

			project.setFileName(fileName);
			project.setModified(false);

			return true;
		}
	
	private:
		wxWindow* m_Parent{};
	};

	struct SaveProject
	{
		SaveProject(wxWindow* parent)
			: m_Parent{ parent }
		{
		}

		bool operator()(IndustryProject& project)
		{
			const std::string& fileName = project.fileName();
			if (fileName.empty() || !std::filesystem::exists(fileName))
			{
				SaveProjectAs saver{ m_Parent };
				saver(project);
			}
			else
			{
				std::unique_ptr<IIndastrySaver> saver = std::make_unique<JsonIndustrySaver>();
				saver->save(
					fileName,
					project);

				project.setModified(false);
			}

			return true;
		}

	private:
		wxWindow* m_Parent{};
	};

	struct AddTypesProject
	{
		AddTypesProject(wxWindow* parent, const std::string& label)
			: m_Parent{ parent }, m_Label{ label }
		{
		}

		void operator()(IndustryProject& project, auto& dst)
		{
			std::unique_ptr<FormAddTypesText> dialog = std::make_unique<FormAddTypesText>(m_Parent, m_Label);

			if (dialog->ShowModal() == wxID_OK)
			{
				std::vector<std::string> stringTypes = dialog->get();
				VectorStrToTypeIndustry strsToTypes{};
				auto materials = dst.copy();
				strsToTypes(stringTypes, materials);
				dst.update(std::move(materials));

				project.setModified(true);
			}
		}

	private:
		wxWindow* m_Parent{};
		std::string m_Label;
	};

	struct RemoveTypesProject
	{
		void operator()(IndustryProject& project, auto& dst, std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			std::reverse(std::begin(selected), std::end(selected));
			for (const long& i : selected)
			{
				dst.erase(i);
			}

			project.setModified(true);
		}
	};

	struct UpdateBlueprintList
	{
		void operator()(IndustryProject& project)
		{
			project.m_BlueprintsList.clear();

			MaterialsToBlueprints mattobps{};
			std::vector<BlueprintProject> blueprints;
			mattobps(project.getTypeProjectIDs(), blueprints);
			std::sort(std::begin(blueprints), std::end(blueprints), BlueprintProjectSortByWeightName());
			project.m_BlueprintsList.update(std::move(blueprints));

			project.restoreSystems();
			project.restoreME();
			project.restoreMaxRunsPerJob();
		}
	};

	struct SetSolarSystem
	{
		void operator()(
			IndustryProject& project,
			const SolarSystemRecord& solSystem,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto& container = project.m_BlueprintsList.get();
			for (const long& i : selected)
			{
				auto& element = container[i];

				element.setSolarSystem(solSystem);
				project.m_BPSystem[element.m_Blueprint.id()] = solSystem;
			}

			project.setModified(true);
		}
	};

	struct SetMeBlueprintProject
	{
		void operator()(
			IndustryProject& project,
			const EVE::Assets::BlueprintME me,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto& container = project.m_BlueprintsList.get();
			for (const long& i : selected)
			{
				auto& element = container[i];
				if (element.m_Blueprint.isReaction())
				{
					continue;
				}

				element.m_ME.m_BpME = me;
				project.m_BPME[element.m_Blueprint.id()].m_BpME = me;
			}

			project.setModified(true);
		}
	};

	struct SetMeStructProject
	{
		void operator()(
			IndustryProject& project,
			const EVE::Assets::StructureME me,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto& container = project.m_BlueprintsList.get();
			for (const long& i : selected)
			{
				auto& element = container[i];
				if (element.m_Blueprint.isReaction())
				{
					continue;
				}

				element.m_ME.m_StructME = me;
				project.m_BPME[element.m_Blueprint.id()].m_StructME = me;
			}

			project.setModified(true);
		}
	};

	struct SetMeRigProject
	{
		void operator()(
			IndustryProject& project,
			const EVE::Assets::RigME me,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto& container = project.m_BlueprintsList.get();
			for (const long& i : selected)
			{
				auto& element = container[i];
				element.m_ME.m_RigME = me;
				project.m_BPME[element.m_Blueprint.id()].m_RigME = me;
			}

			project.setModified(true);
		}
	};

	struct SetMaximumRuns
	{
		void operator()(
			IndustryProject& project,
			const std::uint64_t runs,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto& container = project.m_BlueprintsList.get();
			for (const long& i : selected)
			{
				auto& element = container[i];
				element.m_MaxRunsPerJob = runs;
				project.m_BPMaxRunsPreJob[element.m_Blueprint.id()] = runs;
			}

			project.setModified(true);
		}
	};


	struct SetStructureRoleBonus
	{
		void operator()(
			IndustryProject& project,
			const std::uint64_t bonus,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto& container = project.m_BlueprintsList.get();
			for (const long& i : selected)
			{
				auto& element = container[i];
				element.m_StructRoleBonus = (double)bonus / 100.0;
			}

			project.setModified(true);
		}
	};

	struct SetFacilityTax
	{
		void operator()(
			IndustryProject& project,
			const double tax,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto& container = project.m_BlueprintsList.get();
			for (const long& i : selected)
			{
				auto& element = container[i];
				element.m_FacilityTax = tax / 100.0;
			}

			project.setModified(true);
		}
	};

	struct SetStageStatus
	{
		void operator()(
			IndustryProject& project,
			const StageStatus status,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto& container = project.m_ProductionStages.get();
			for (const long& line : selected)
			{
				auto& item = container.at(line);
				item.setStatus(status);
			}

			project.setModified(true);
		}
	};

	struct CalculateIndustry
	{
		void operator()(IndustryProject& project, const bool fullCalculation = true)
		{
			std::vector<MaterialBase> types_base;
			std::vector<MaterialBlueprint> types_blueprints;
			std::vector<ProductionStage> prod_stages;

			IndustryCalculation industryCalculation(project, fullCalculation);
			industryCalculation.getRawMaterials(types_base);
			industryCalculation.getBpsMaterials(types_blueprints);
			industryCalculation.getStages(prod_stages);

			std::sort(std::begin(types_base), std::end(types_base), MaterialsBaseSortByGroupIdTypeName());
			std::sort(std::begin(types_blueprints), std::end(types_blueprints), MaterialsBlueprintSortByWeightName());

			project.m_TypesBase.update(std::move(types_base));
			project.m_TypesBlueprint.update(std::move(types_blueprints));
			project.m_ProductionStages.update(std::move(prod_stages));

			project.setModified(true);
		}
	};

	struct GetMaterialsStages
	{
		void operator()(
			const IndustryProject& project,
			const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			std::vector<MaterialProject> tmpTypes;

			const auto& stagesProject = project.m_ProductionStages.get();
			for (const long stageIndex : selected)
			{
				const ProductionStage& stage = stagesProject[stageIndex];
				const std::uint32_t type_id = stage.m_Blueprint.producedID();
				const std::uint64_t quantity = stage.m_Quantity;

				auto ittr = std::find_if(std::begin(tmpTypes), std::end(tmpTypes),
					[type_id](const MaterialProject& elem)
					{
						return elem.m_Type.id() == type_id;
					});

				if (ittr != std::end(tmpTypes))
				{
					ittr->add(quantity);
				}
				else
				{
					tmpTypes.emplace_back(TypeRecord{ type_id }, quantity);
				}
			}

			IndustryProject tmpProject;
			tmpProject.m_TypesProject.update(std::move(tmpTypes));
			tmpProject.m_BlueprintsList.update(project.m_BlueprintsList.copy());
			
			std::vector<MaterialProject> tmpMaterials;
			IndustryCalculation industryCalculation(tmpProject, false);
			industryCalculation.getAllMaterialsNoIndustryMaterials(tmpMaterials);

			std::sort(std::begin(tmpMaterials), std::end(tmpMaterials), MaterialProjectSortByGroupIdTypeName());

			std::unique_ptr<FormMaterialsStages> dialog = std::make_unique<FormMaterialsStages>(std::move(tmpMaterials));
			dialog->ShowModal();
		}
	};

	struct AddToStock
	{
		void operator()(IndustryProject& project, auto& dst, const std::vector<long>& selected)
		{
			if (selected.empty())
			{
				return;
			}

			auto tmpStock = project.m_Stock.copy();
			const auto& container = dst.get();
			for (const long index : selected)
			{
				const std::uint32_t type_id = container[index].m_Type.id();
				const std::uint64_t quantity = container[index].m_Type.getQuantity();
				auto ittr = std::find_if(std::begin(tmpStock), std::end(tmpStock),
					[type_id](const auto& elem)
					{
						return elem.m_Type.id() == type_id;
					});

				if (ittr != std::end(tmpStock))
				{
					ittr->add(quantity);
				}
				else
				{
					tmpStock.emplace_back(TypeRecord{ type_id }, quantity);
				}
			}

			project.m_Stock.update(std::move(tmpStock));

			CalculateIndustry calcIndy{};
			calcIndy(project);
		}
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_INDUSTRYPROJECTUTILITY_HPP_