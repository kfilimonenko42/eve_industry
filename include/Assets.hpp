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

#ifndef _EVEINDUSTRY_ASSETS_HPP_
#define _EVEINDUSTRY_ASSETS_HPP_

#include <thread>
#include <concepts>
#include <wx/wx.h>

#include "AssetContainer.hpp"
#include "JsonAssetsLoader.hpp"

namespace EVE::Industry
{

	void tload(auto& container)
	{
		container.load(std::make_unique<EVE::Assets::JsonLoader>());
	}

	class Assets
	{
	public:
		using BlueprintsContainer = EVE::Assets::BlueprintsContainer;
		using BlueprintsSettingsContainer = EVE::Assets::BlueprintsSettingsContainer;
		using TypesContainer = EVE::Assets::TypesContainer;
		using CategoriesContainer = EVE::Assets::CategoriesContainer;
		using GroupsContainer = EVE::Assets::GroupsContainer;
		using MarketGroupsContainer = EVE::Assets::MarketGroupsContainer;
		using PISchemasContainer = EVE::Assets::PISchemasContainer;
		using RegionsContainer = EVE::Assets::RegionsContainer;
		using SolarSystemsContainer = EVE::Assets::SolarSystemsContainer;
		using StationsContainer = EVE::Assets::StationsContainer;

		Assets();
		~Assets() = default;

		Assets(const Assets& other) = delete;
		Assets& operator=(const Assets& other) = delete;
		Assets(Assets&& other) = delete;
		Assets& operator=(Assets&& other) = delete;

		static Assets& Instance();

	public:
		BlueprintsContainer m_BlueprintsContainer;
		BlueprintsSettingsContainer m_BlueprintsSettingsContainer;
		TypesContainer m_TypesContainer;
		CategoriesContainer m_CategoriesContainer;
		GroupsContainer m_GroupsContainer;
		MarketGroupsContainer m_MarketGroupsContainer;
		PISchemasContainer m_PISchemasContainer;
		RegionsContainer m_RegionsContainer;
		SolarSystemsContainer m_SolarSystemsContainer;
		StationsContainer m_StationsContainer;

	private:
		void load();
	};



} // namespace EVE::Industry

#endif // _EVEINDUSTRY_ASSETS_HPP_