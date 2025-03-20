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

#ifndef _EVEASSET_JSONLOADER_HPP_
#define _EVEASSET_JSONLOADER_HPP_

#include <utility>
#include <string>
#include <filesystem>
#include <cassert>
#include <nlohmann/json.hpp>

#include "IBaseLoaders.hpp"
#include "Settings.hpp"
#include "JsonHelper.hpp"
#include "Logger.hpp"

namespace EVE::Assets
{

	class JsonLoader final : public IBaseLoader
	{
	public:
		JsonLoader() = default;
		explicit JsonLoader(std::string&& source);

		void load(std::vector<Agent>& _container) override;
		void load(std::vector<Constellation>& _container) override;
		void load(std::vector<Region>& _container) override;
		void load(std::vector<SolarSystem>& _container) override;
		void load(std::vector<Station>& _container) override;
		void load(std::vector<Blueprint>& _container) override;
		void load(std::vector<BlueprintSettings>& _container) override;
		void load(std::vector<Type>& _container) override;
		void load(std::vector<MarketGroup>& _container) override;
		void load(std::vector<Group>& _container) override;
		void load(std::vector<Category>& _container) override;
		void load(std::vector<PI>& _container) override;
		void load(std::vector<Order>& _container) override;
		void load(std::vector<SystemCostIndices>& _container) override;

	private:
		std::string m_Source;
	};

	void from_json(const nlohmann::json& j, Agent& v);
	void from_json(const nlohmann::json& j, Constellation& v);
	void from_json(const nlohmann::json& j, Region& v);
	void from_json(const nlohmann::json& j, SolarSystem& v);
	void from_json(const nlohmann::json& j, Station& v);
	void from_json(const nlohmann::json& j, Point& v);
	void from_json(const nlohmann::json& j, Blueprint& v);
	void from_json(const nlohmann::json& j, BlueprintSettings& v);
	void from_json(const nlohmann::json& j, std::vector<Material>& v);
	void from_json(const nlohmann::json& j, std::vector<InventionProduct>& v);
	void from_json(const nlohmann::json& j, Type& v);
	void from_json(const nlohmann::json& j, MarketGroup& v);
	void from_json(const nlohmann::json& j, Group& v);
	void from_json(const nlohmann::json& j, Category& v);
	void from_json(const nlohmann::json& j, PI& v);
	void from_json(const nlohmann::json& j, Order& v);
	void from_json(const nlohmann::json& j, SystemCostIndices& v);

	template<class T>
	bool json_load(const nlohmann::json& js, std::vector<T>& _container) noexcept
	{
		Log::LOG_DEBUG(std::format("reserve container (size: {})", js.size()));
		_container.reserve(js.size());

		for (const nlohmann::json& elem : js)
		{
			try
			{
				_container.emplace_back(elem.get<T>());
			}
			catch (const std::runtime_error& er)
			{
				Log::LOG_ERROR(er.what());
			}
		}

		return true;
	}

	template<class T>
	bool json_load(const std::string _path, std::vector<T>& _container) noexcept
	{
		Log::LOG_DEBUG("read json file: " + _path);

		JsonHelper jh(std::filesystem::current_path().string() + _path);

		nlohmann::json js;
		if (jh.load(js))
		{
			json_load(js, _container);
		}

		return true;
	}

} // namespace EVE::Assets

#endif // _EVEASSET_JSONLOADER_HPP_