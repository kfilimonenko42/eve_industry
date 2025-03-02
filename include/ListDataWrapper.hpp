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

#ifndef _EVEINDUSTRY_LISTDATAWRAPPER_HPP_
#define _EVEINDUSTRY_LISTDATAWRAPPER_HPP_

#include <vector>
#include <cassert>
#include <string>
#include <cstdint>
#include <utility>
#include <mutex>
#include <memory>
#include <map>
#include <wx/wx.h>

#include "IListInfoUpdater.hpp"
#include "EsiOrderSettings.hpp"

namespace EVE::Industry
{

	template<typename T>
	class ListDataWrapper
	{
	public:
		ListDataWrapper() = default;
		~ListDataWrapper();

		std::vector<T>& get();
		const std::vector<T>& get() const;
		std::vector<T> copy() const;
		void clear();
		std::size_t size() const;
		bool empty() const;
		void erase(const std::size_t index);
		void update(std::vector<T>&& src);
		void addUpdater(std::unique_ptr<IListInfoUpdater> updater);

		void setPrices();
		void setImages(auto vCtrlList);
		void setEsiSettings(const EsiOrderSettings& esiSettings);

	private:
		void stopUpdaters();
		void startUpdaters(const std::vector<std::uint32_t>& ids);

	private:
		std::vector<T> m_Data;
		std::mutex m_Mutex;
		std::vector<std::unique_ptr<IListInfoUpdater>> m_Updaters;
		EsiOrderSettings m_EsiSettings{};
	};

	template<typename T>
	inline ListDataWrapper<T>::~ListDataWrapper()
	{
		m_Updaters.clear();
	}

	template<typename T>
	inline std::vector<T>& ListDataWrapper<T>::get()
	{
		return m_Data;
	}

	template<typename T>
	inline const std::vector<T>& ListDataWrapper<T>::get() const
	{
		return m_Data;
	}

	template<typename T>
	inline std::vector<T> ListDataWrapper<T>::copy() const
	{
		return m_Data;
	}

	template<typename T>
	inline void ListDataWrapper<T>::clear()
	{
		std::scoped_lock sl(m_Mutex);
		m_Data.clear();
	}

	template<typename T>
	inline std::size_t ListDataWrapper<T>::size() const
	{
		return m_Data.size();
	}

	template<typename T>
	inline bool ListDataWrapper<T>::empty() const
	{
		return m_Data.empty();
	}

	template<typename T>
	inline void ListDataWrapper<T>::erase(const std::size_t index)
	{
		std::scoped_lock sl(m_Mutex);
		m_Data.erase(std::next(std::begin(m_Data), index));
	}

	template<typename T>
	inline void ListDataWrapper<T>::update(std::vector<T>&& src)
	{
		stopUpdaters();

		{
			m_Data.clear();
		}

		std::vector<std::uint32_t> ids;

		{
			std::scoped_lock sl(m_Mutex);
			m_Data = std::move(src);

			for (const auto& elem : m_Data)
			{
				ids.push_back(elem.id());
			}
		}

		startUpdaters(ids);
	}

	template<typename T>
	inline void ListDataWrapper<T>::addUpdater(std::unique_ptr<IListInfoUpdater> updater)
	{
		if (updater)
		{
			m_Updaters.push_back(std::move(updater));
		}
	}

	template<typename T>
	inline void ListDataWrapper<T>::setPrices()
	{
		AppraisalContainer& container = AppraisalContainer::Instance();

		std::scoped_lock sl(m_Mutex);
		for (auto& elem : m_Data)
		{
			if (container.hasPrice(elem.id(), m_EsiSettings))
			{
				const auto& price = container.getPrice(elem.id(), m_EsiSettings);
				elem.m_Type.setPriceSell(price.m_PriceSell);
				elem.m_Type.setPriceBuy(price.m_PriceBuy);
			}
		}
	}

	template<typename T>
	inline void ListDataWrapper<T>::setImages(auto vCtrlList)
	{
		BitmapContainer& container = BitmapContainer::Instance();

		wxVector<wxBitmapBundle> m_vIcons;
		std::map<std::uint32_t, std::size_t> m_vIdsIcons;

		std::scoped_lock sl(m_Mutex);
		for (auto& elem : m_Data)
		{
			if (container.has16(elem.id()))
			{
				container.get16(elem.id(), m_vIcons, m_vIdsIcons);
			}
		}

		vCtrlList->updateImages(m_vIcons, m_vIdsIcons);
	}

	template<typename T>
	inline void ListDataWrapper<T>::setEsiSettings(const EsiOrderSettings& esiSettings)
	{
		m_EsiSettings = esiSettings;
	}

	template<typename T>
	inline void ListDataWrapper<T>::stopUpdaters()
	{
		for (size_t index = 0; index < m_Updaters.size(); ++index)
		{
			m_Updaters[index]->stop();
		}
	}

	template<typename T>
	inline void ListDataWrapper<T>::startUpdaters(const std::vector<std::uint32_t>& ids)
	{
		for (size_t index = 0; index < m_Updaters.size(); ++index)
		{
			m_Updaters[index]->start(ids);
		}
	}

} // EVE::Industry

#endif // _EVEINDUSTRY_LISTDATAWRAPPER_HPP_