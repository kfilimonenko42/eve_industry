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

#ifndef _EVEASSETS_ASSETCONTAINER_HPP_
#define _EVEASSETS_ASSETCONTAINER_HPP_

#include <vector>
#include <memory>
#include <mutex>
#include <algorithm>
#include <concepts>
#include <cstdint>

#include "IBaseLoaders.hpp"

namespace EVE::Assets
{

	template<typename T>
	concept TSupportsLessThan = requires(T x) { x < x; };

	template<typename T>
	auto searh_by_name(const std::vector<T>& container, const std::string& value)
	{
		return std::find_if(std::begin(container), std::end(container),
			[&value](const T& elem)
			{
				return (elem.m_NameSearch == value);
			}
		);
	}

	template<typename T>
	auto searh_by_id(const std::vector<T>& container, const std::uint32_t value)
	{
		if constexpr (TSupportsLessThan<T>)
		{
			return std::lower_bound(std::begin(container), std::end(container), value,
				[](const T& elem, const std::uint32_t value)
				{
					return (elem.m_ID < value);
				}
			);
		}
		else
		{
			return std::find_if(std::begin(container), std::end(container),
				[value](const T& elem)
				{
					return (elem.m_ID == value);
				}
			);
		}
	}

	template<typename T>
	class AssetContainer
	{
	private:
		std::vector<T> m_Container;
		std::mutex m_Mutex;

	public:
		explicit AssetContainer() = default;
		~AssetContainer() = default;

		AssetContainer(const EVE::Assets::AssetContainer<T>& tmp) = delete;
		EVE::Assets::AssetContainer<T>& operator=(const EVE::Assets::AssetContainer<T>& tmp) = delete;
		AssetContainer(EVE::Assets::AssetContainer<T>&& tmp) = delete;
		EVE::Assets::AssetContainer<T>& operator=(EVE::Assets::AssetContainer<T>&& tmp) = delete;

		void load(std::unique_ptr<EVE::Assets::IBaseLoader> loader)
		{
			std::scoped_lock lg(m_Mutex);

			if (!m_Container.empty())
			{
				m_Container.clear();
			}

			loader->load(m_Container);

			if constexpr(TSupportsLessThan<T>)
			{
				std::sort(std::begin(m_Container), std::end(m_Container));
			}
		}

		std::size_t size() const
		{
			return m_Container.size();
		}

		std::size_t empty() const
		{
			return m_Container.empty();
		}

		decltype(auto) begin()
		{
			return std::begin(m_Container);
		}

		decltype(auto) end()
		{
			return std::end(m_Container);
		}

		decltype(auto) cbegin() const
		{
			return std::begin(m_Container);
		}

		decltype(auto) cend() const
		{
			return std::end(m_Container);
		}

		[[nodiscard]] const std::vector<T>& get_container() const
		{
			return m_Container;
		}

		/// <summary>
		/// get an id type by name
		/// </summary>
		/// <param name="_name"></param>
		/// <returns></returns>
		[[nodiscard]] std::tuple<bool, std::uint32_t> id(const std::string& _name) const
		{
			if (!_name.empty())
			{
				auto ittr = searh_by_name(m_Container, _name);

				if (ittr != m_Container.end())
				{
					return std::make_tuple(true, ittr->m_ID);
				}
			}

			return std::make_tuple(false, 0);
		}

		/// <summary>
		/// get a pointer to an element by name
		/// </summary>
		/// <param name="_name"></param>
		/// <returns></returns>
		[[nodiscard]] std::tuple<bool, const T*> element(const std::string& _name) const
		{
			if (!_name.empty())
			{
				auto ittr = searh_by_name(m_Container, _name);

				if (ittr != m_Container.end())
				{
					return std::make_tuple(true, &(*ittr));
				}
			}

			return std::make_tuple(false, nullptr);
		}

		/// <summary>
		/// get a pointer to an element by id
		/// </summary>
		/// <param name="_id"></param>
		/// <returns></returns>
		[[nodiscard]] std::tuple<bool, const T*> element(const std::uint32_t _id) const
		{
			if (_id > 0)
			{
				auto ittr = searh_by_id(m_Container, _id);

				if (ittr != m_Container.end() && ittr->m_ID == _id)
				{
					return std::make_tuple(true, &(*ittr));
				}
			}

			return std::make_tuple(false, nullptr);
		}

		/// <summary>
		/// get "name (id)" string
		/// </summary>
		/// <param name="_id"></param>
		/// <returns></returns>
		[[nodiscard]] std::tuple<bool, std::string> toString(const std::uint32_t _id) const
		{
			if (_id > 0)
			{
				auto ittr = searh_by_id(m_Container, _id);

				if (ittr != m_Container.end() && ittr->m_ID == _id)
				{
					return std::make_tuple(true, std::format("{} (id: {})", ittr->m_Name, ittr->m_ID));
				}
			}

			return std::make_tuple(false, std::string());
		}
	};

	using AgentsContainer = AssetContainer<Agent>;
	using ConstellationsContainer = AssetContainer<Constellation>;
	using RegionsContainer = AssetContainer<Region>;
	using SolarSystemsContainer = AssetContainer<SolarSystem>;
	using StationsContainer = AssetContainer<Station>;
	using BlueprintsContainer = AssetContainer<Blueprint>;
	using BlueprintsSettingsContainer = AssetContainer<BlueprintSettings>;
	using TypesContainer = AssetContainer<Type>;
	using CategoriesContainer = AssetContainer<Category>;
	using GroupsContainer = AssetContainer<Group>;
	using MarketGroupsContainer = AssetContainer<MarketGroup>;
	using PISchemasContainer = AssetContainer<PI>;
	using OrderContainer = AssetContainer<Order>;

} // namespace EVE::Assets

#endif // _EVEASSETS_ASSETCONTAINER_HPP_