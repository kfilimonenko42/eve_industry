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

#include "Assets.hpp"

EVE::Industry::Assets::Assets()
{
	load();
}

EVE::Industry::Assets& EVE::Industry::Assets::Instance()
{
	static Assets instance{};
	return instance;
}

void EVE::Industry::Assets::load()
{
	{
		std::jthread thread1(&tload<BlueprintsContainer>, std::ref(m_BlueprintsContainer));
		std::jthread thread2(&tload<BlueprintsSettingsContainer>, std::ref(m_BlueprintsSettingsContainer));
		std::jthread thread3(&tload<TypesContainer>, std::ref(m_TypesContainer));
	}
	{
		std::jthread thread1(&tload<CategoriesContainer>, std::ref(m_CategoriesContainer));
		std::jthread thread2(&tload<GroupsContainer>, std::ref(m_GroupsContainer));
		std::jthread thread3(&tload<MarketGroupsContainer>, std::ref(m_MarketGroupsContainer));
		std::jthread thread4(&tload<PISchemasContainer>, std::ref(m_PISchemasContainer));
	}
	{
		std::jthread thread1(&tload<RegionsContainer>, std::ref(m_RegionsContainer));
		std::jthread thread2(&tload<SolarSystemsContainer>, std::ref(m_SolarSystemsContainer));
		std::jthread thread3(&tload<StationsContainer>, std::ref(m_StationsContainer));
	}
	{
		std::jthread thread1(&tload_sci<SystemsCostIndicesContainer>, std::ref(m_SystemsCostIndicesContainer));
	}
}