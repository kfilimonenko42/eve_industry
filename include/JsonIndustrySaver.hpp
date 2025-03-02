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

#ifndef _EVEINDUSTRY_JSONINDUSTRYSAVER_HPP_
#define _EVEINDUSTRY_JSONINDUSTRYSAVER_HPP_

#include <nlohmann/json.hpp>

#include "IIndustrySaver.hpp"

namespace EVE::Industry
{

	class JsonIndustrySaver : public IIndastrySaver
	{
	public:
		JsonIndustrySaver() = default;

        void save(const std::string& fileName, const IndustryProject& source) override;
	};

    template<typename... Args>
    inline void prepareDataJson(const auto& source, nlohmann::json& dst, Args... args)
    {
        if (source.empty())
        {
            return;
        }

        for (const auto& elem : source.get())
        {
            try
            {
                dst.push_back(nlohmann_to_json(elem, args...));
            }
            catch (const std::exception& ex)
            {
                Log::LOG_ERROR(ex.what());
            }
        }
    }

	nlohmann::json nlohmann_to_json(const MaterialProject& elem);
	nlohmann::json nlohmann_to_json(const BlueprintProject& elem, const std::unordered_map<std::uint32_t, EVE::Assets::BlueprintMaterialEfficiency>& bpme);
    nlohmann::json nlohmann_to_json(const MaterialBase& elem);
    nlohmann::json nlohmann_to_json(const MaterialBlueprint& elem);
    nlohmann::json nlohmann_to_json(const ProductionStage& elem);

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_JSONINDUSTRYSAVER_HPP_