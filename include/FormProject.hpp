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

#ifndef _EVEINDUSTRY_FORMPROJECT_HPP_
#define _EVEINDUSTRY_FORMPROJECT_HPP_

#include <vector>
#include <algorithm>
#include <cassert>
#include <optional>
#include <utility>
#include <memory>
#include <functional>
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <wx/event.h>

#include "IndustryProject.hpp"
#include "wxPageAvailableMaterials.hpp"
#include "SolarSystemRecord.hpp"

namespace EVE::Industry
{

	class FormProject : public wxWindow
	{
	public:
		explicit FormProject(wxWindow* parent);
		FormProject(wxWindow* parent, const std::string& projName);
		virtual ~FormProject() = default;

		const IndustryProject& project() const;
		const std::string& name() const;
		bool load();
		bool saveAs();
		bool save();
		void bindFunUpdPage(std::function<void()> func);
		void addTypes();
		void deleteTypes(std::vector<long>& selected);
		void deleteAllTypes();
		void addAvailableTypes();
		void deleteAvailableTypes(std::vector<long>& selected);
		void deleteAllAvailableTypes();
		void getBlueprints();
		void setSolarSystem(const SolarSystemRecord& solSystem, const std::vector<long>& selected);
		void setME(const EVE::Assets::BlueprintME me, const std::vector<long>& selected);
		void setME(const EVE::Assets::StructureME me, const std::vector<long>& selected);
		void setME(const EVE::Assets::RigME me, const std::vector<long>& selected);
		void setMaximumRuns(const std::uint64_t runs, const std::vector<long>& selected);
		void setStageStatus(const StageStatus status, const std::vector<long>& selected);
		void showMaterialsStages(const std::vector<long>& selected);
		void calculateProject();

	private:
		void createControls();
		void updateAllLists();
		void updateMaterialsProjectList();
		void updateBlueprintsProjectList();
		void updateMaterialsAvailableList();
		void updateIndustryResultLists();
		void updateStageList();
		void updateNamePage();

	private:
		IndustryProject m_Project;
		wxPanel* m_basePanel = new wxPanel(this, wxID_ANY);
		wxNotebook* m_baseNotebook = new wxNotebook(m_basePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
		wxWindow* m_PageMaterialsProject{};
		wxWindow* m_PageBlueprintsProject{};
		wxWindow* m_PageMaterialsBase{};
		wxWindow* m_PageMaterialsBlueprint{};
		wxWindow* m_PageProductionStages{};
		wxPageAvailableMaterials* m_PageAvailableMaterials{};
		std::function<void()> m_fUpdNamePage;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMPROJECT_HPP_