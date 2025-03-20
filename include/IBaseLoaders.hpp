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

#ifndef _EVEASSETS_IASSETLOADER_HPP_
#define _EVEASSETS_IASSETLOADER_HPP_

#include <vector>

#include "Agent.hpp"
#include "Constellation.hpp"
#include "Region.hpp"
#include "SolarSystem.hpp"
#include "Station.hpp"
#include "Blueprint.hpp"
#include "BlueprintSettings.hpp"
#include "Type.hpp"
#include "MarketGroup.hpp"
#include "Group.hpp"
#include "Category.hpp"
#include "PI.hpp"
#include "Order.hpp"
#include "SystemCostIndices.hpp"

namespace EVE::Assets
{

	class IBaseLoader
	{
	public:
		virtual ~IBaseLoader() = default;

		virtual void load(std::vector<Agent>& _container) = 0;
		virtual void load(std::vector<Constellation>& _container) = 0;
		virtual void load(std::vector<Region>& _container) = 0;
		virtual void load(std::vector<SolarSystem>& _container) = 0;
		virtual void load(std::vector<Station>& _container) = 0;
		virtual void load(std::vector<Blueprint>& _container) = 0;
		virtual void load(std::vector<BlueprintSettings>& _container) = 0;
		virtual void load(std::vector<Type>& _container) = 0;
		virtual void load(std::vector<MarketGroup>& _container) = 0;
		virtual void load(std::vector<Group>& _container) = 0;
		virtual void load(std::vector<Category>& _container) = 0;
		virtual void load(std::vector<PI>& _container) = 0;
		virtual void load(std::vector<Order>& _container) = 0;
		virtual void load(std::vector<SystemCostIndices>& _container) = 0;
	};

} // EVE::Assets

#endif // _EVEASSETS_IASSETLOADER_HPP_