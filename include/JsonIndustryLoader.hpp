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

#ifndef _EVEINDUSTRY_JSONINDUSTRYLOADER_HPP_
#define _EVEINDUSTRY_JSONINDUSTRYLOADER_HPP_

#include <nlohmann/json.hpp>

#include "IIndustryLoader.hpp"

namespace EVE::Industry
{

	class JsonIndustryLoader : public IIndustryLoader
	{
	public:
		JsonIndustryLoader() = default;

		void load(const std::string& fileName, IndustryProject& dst) override;

    private:
        void clearProject(IndustryProject& dst);
        void readMaterialsProject(const nlohmann::json& src, ListDataWrapper<MaterialProject>& dst);
        void readStock(const nlohmann::json& src, ListDataWrapper<MaterialProject>& dst);
        void readBlueprintsProject(const nlohmann::json& src, IndustryProject& dst);
        void readTypesRaw(const nlohmann::json& src, ListDataWrapper<MaterialBase>& dst);
        void readTypesBps(const nlohmann::json& src, ListDataWrapper<MaterialBlueprint>& dst);
        void readStages(const nlohmann::json& src, ListDataWrapper<ProductionStage>& dst);
	};

}

#endif // _EVEINDUSTRY_JSONINDUSTRYLOADER_HPP_