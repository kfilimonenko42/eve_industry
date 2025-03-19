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

#include "FormProject.hpp"
#include "wxPageMaterialsProject.hpp"
#include "wxPageBlueprintsProject.hpp"
#include "wxPageMaterialsBase.hpp"
#include "wxPageMaterialsBlueprint.hpp"
#include "wxPageProductionStages.hpp"
#include "wxPageAvailableMaterials.hpp"
#include "IndustryProject_utility.hpp"

EVE::Industry::FormProject::FormProject(wxWindow* parent)
	: wxWindow(parent, wxID_ANY)
{
	createControls();
}

EVE::Industry::FormProject::FormProject(wxWindow* parent, const std::string& projName)
	: wxWindow(parent, wxID_ANY), m_Project{ projName }
{
	createControls();
}

const EVE::Industry::IndustryProject& EVE::Industry::FormProject::project() const
{
	return m_Project;
}

bool EVE::Industry::FormProject::load()
{
	LoadProject loader{ this };
	const bool result = loader(m_Project);

	updateAllLists();

	return result;
}

bool EVE::Industry::FormProject::saveAs()
{
	SaveProjectAs saver{ this };
	if (saver(m_Project))
	{
		updateNamePage();
		return true;
	}

	return false;
}

bool EVE::Industry::FormProject::save()
{
	SaveProject saver{ this };
	if (saver(m_Project))
	{
		updateNamePage();
		return true;
	}

	return false;
}

void EVE::Industry::FormProject::bindFunUpdPage(std::function<void()> func)
{
	if (func)
	{
		m_fUpdNamePage = func;
	}
}

void EVE::Industry::FormProject::addTypes()
{
	AddTypesProject adder(this, "add types for industry");
	adder(m_Project, m_Project.m_TypesProject);

	updateMaterialsProjectList();
	updateNamePage();
}

void EVE::Industry::FormProject::deleteTypes(std::vector<long>& selected)
{
	RemoveTypesProject remover{};
	remover(m_Project, m_Project.m_TypesProject, selected);

	updateMaterialsProjectList();
	updateNamePage();
}

void EVE::Industry::FormProject::deleteAllTypes()
{
	m_Project.m_TypesProject.clear();
	m_Project.setModified(true);

	updateMaterialsProjectList();
	updateNamePage();
}

void EVE::Industry::FormProject::addAvailableTypes()
{
	AddTypesProject adder(this, "stock");
	adder(m_Project, m_Project.m_Stock);

	updateMaterialsAvailableList();
	updateNamePage();
}

void EVE::Industry::FormProject::deleteAvailableTypes(std::vector<long>& selected)
{
	RemoveTypesProject remover{};
	remover(m_Project, m_Project.m_Stock, selected);

	updateMaterialsAvailableList();
	updateNamePage();
}

void EVE::Industry::FormProject::deleteAllAvailableTypes()
{
	m_Project.m_Stock.clear();
	m_Project.setModified(true);

	updateMaterialsAvailableList();
	updateNamePage();
}

void EVE::Industry::FormProject::getBlueprints()
{
	UpdateBlueprintList updBpList{};
	updBpList(m_Project);

	updateBlueprintsProjectList();
}

void EVE::Industry::FormProject::setSolarSystem(const SolarSystemRecord& solSystem, const std::vector<long>& selected)
{
	SetSolarSystem setSS{};
	setSS(m_Project, solSystem, selected);

	updateBlueprintsProjectList();
	updateNamePage();
}

void EVE::Industry::FormProject::setME(const EVE::Assets::BlueprintME me, const std::vector<long>& selected)
{
	SetMeBlueprintProject setME{};
	setME(m_Project, me, selected);

	updateBlueprintsProjectList();
	updateNamePage();
}

void EVE::Industry::FormProject::setME(const EVE::Assets::StructureME me, const std::vector<long>& selected)
{
	SetMeStructProject setME{};
	setME(m_Project, me, selected);

	updateBlueprintsProjectList();
	updateNamePage();
}

void EVE::Industry::FormProject::setME(const EVE::Assets::RigME me, const std::vector<long>& selected)
{
	SetMeRigProject setME{};
	setME(m_Project, me, selected);

	updateBlueprintsProjectList();
	updateNamePage();
}

void EVE::Industry::FormProject::setMaximumRuns(const std::uint64_t runs, const std::vector<long>& selected)
{
	SetMaximumRuns setMaxRuns{};
	setMaxRuns(m_Project, runs, selected);

	updateBlueprintsProjectList();
	updateNamePage();
}

void EVE::Industry::FormProject::setStageStatus(const StageStatus status, const std::vector<long>& selected)
{
	SetStageStatus setStageStatus{};
	setStageStatus(m_Project, status, selected);

	updateStageList();
	updateNamePage();
}

void EVE::Industry::FormProject::showMaterialsStages(const std::vector<long>& selected)
{
	GetMaterialsStages materialsStages{};
	materialsStages(m_Project, selected);
}

void EVE::Industry::FormProject::addStockFromRawMaterials(const std::vector<long>& selected)
{
	AddToStock addStock{};
	addStock(m_Project, m_Project.m_TypesBase, selected);

	updateIndustryResultLists();
	updateMaterialsAvailableList();
	updateNamePage();
}

void EVE::Industry::FormProject::addStockFromBpMaterials(const std::vector<long>& selected)
{
	AddToStock addStock{};
	addStock(m_Project, m_Project.m_TypesBlueprint, selected);

	updateIndustryResultLists();
	updateMaterialsAvailableList();
	updateNamePage();
}

const std::string& EVE::Industry::FormProject::name() const
{
	return m_Project.name();
}

void EVE::Industry::FormProject::calculateProject()
{
	CalculateIndustry calcIndy{};
	calcIndy(m_Project);

	updateIndustryResultLists();
	updateNamePage();
}

void EVE::Industry::FormProject::createControls()
{
	wxNotebookPage* page1 = new wxNotebookPage(m_baseNotebook, wxID_ANY);
	m_baseNotebook->AddPage(page1, "project");
	m_PageMaterialsProject = new wxPageMaterialsProject(page1, this, &m_Project.m_TypesProject);
	
	wxNotebookPage* page2 = new wxNotebookPage(m_baseNotebook, wxID_ANY);
	m_baseNotebook->AddPage(page2, "stock");
	m_PageAvailableMaterials = new wxPageAvailableMaterials(page2, this, &m_Project.m_Stock);

	wxNotebookPage* page3 = new wxNotebookPage(m_baseNotebook, wxID_ANY);
	m_baseNotebook->AddPage(page3, "blueprints");
	m_PageBlueprintsProject = new wxPageBlueprintsProject(page3, this, &m_Project.m_BlueprintsList);

	wxNotebookPage* page4 = new wxNotebookPage(m_baseNotebook, wxID_ANY);
	m_baseNotebook->AddPage(page4, "materials - raw");
	m_PageMaterialsBase = new wxPageMaterialsBase(page4, this, &m_Project.m_TypesBase);

	wxNotebookPage* page5 = new wxNotebookPage(m_baseNotebook, wxID_ANY);
	m_baseNotebook->AddPage(page5, "materials - bps");
	m_PageMaterialsBlueprint = new wxPageMaterialsBlueprint(page5, this, &m_Project.m_TypesBlueprint);

	wxNotebookPage* page6 = new wxNotebookPage(m_baseNotebook, wxID_ANY);
	m_baseNotebook->AddPage(page6, "stages");
	m_PageProductionStages = new wxPageProductionStages(page6, this, &m_Project.m_ProductionStages);

	wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_sizer->Add(m_baseNotebook, 1, wxEXPAND);
	m_basePanel->SetSizer(panel_sizer);

	wxBoxSizer* top_sizer = new wxBoxSizer(wxHORIZONTAL);
	top_sizer->SetMinSize(500, 250);
	top_sizer->Add(m_basePanel, 1, wxEXPAND);
	SetSizerAndFit(top_sizer);
}

void EVE::Industry::FormProject::updateAllLists()
{
	dynamic_cast<wxPageMaterialsProject*>(m_PageMaterialsProject)->updateList();
	dynamic_cast<wxPageAvailableMaterials*>(m_PageAvailableMaterials)->updateList();
	dynamic_cast<wxPageBlueprintsProject*>(m_PageBlueprintsProject)->updateList();
	dynamic_cast<wxPageMaterialsBase*>(m_PageMaterialsBase)->updateList();
	dynamic_cast<wxPageMaterialsBlueprint*>(m_PageMaterialsBlueprint)->updateList();
	dynamic_cast<wxPageProductionStages*>(m_PageProductionStages)->updateList();
}

void EVE::Industry::FormProject::updateMaterialsProjectList()
{
	dynamic_cast<wxPageMaterialsProject*>(m_PageMaterialsProject)->updateList();
}

void EVE::Industry::FormProject::updateBlueprintsProjectList()
{
	dynamic_cast<wxPageBlueprintsProject*>(m_PageBlueprintsProject)->updateList();
}

void EVE::Industry::FormProject::updateMaterialsAvailableList()
{
	dynamic_cast<wxPageAvailableMaterials*>(m_PageAvailableMaterials)->updateList();
}

void EVE::Industry::FormProject::updateIndustryResultLists()
{
	dynamic_cast<wxPageMaterialsBase*>(m_PageMaterialsBase)->updateList();
	dynamic_cast<wxPageMaterialsBlueprint*>(m_PageMaterialsBlueprint)->updateList();
	updateStageList();
}

void EVE::Industry::FormProject::updateStageList()
{
	dynamic_cast<wxPageProductionStages*>(m_PageProductionStages)->updateList();
}

void EVE::Industry::FormProject::updateNamePage()
{
	if (m_fUpdNamePage)
	{
		m_fUpdNamePage();
	}
}
