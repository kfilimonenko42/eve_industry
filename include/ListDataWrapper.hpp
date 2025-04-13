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
#include <set>
#include <cassert>
#include <string>
#include <cstdint>
#include <utility>
#include <mutex>
#include <memory>
#include <map>
#include <wx/wx.h>

#include "AppraisalContainer.hpp"
#include "BitmapContainer.hpp"

namespace EVE::Industry
{

	template<typename T>
	class ListDataWrapper
	{
	public:
		ListDataWrapper() = default;

		T& operator[](std::size_t index);
		const T& operator[](std::size_t index) const;

		std::vector<T>& get();
		const std::vector<T>& get() const;
		std::vector<std::uint32_t> ids() const;
		std::vector<T> copy() const;
		void clear();
		std::size_t size() const;
		bool empty() const;
		void erase(const std::size_t index);
		void update(std::vector<T>&& src);
		void sendUpdatePrices(int owner_id) const;
		void sendUpdateImages(int owner_id) const;

	private:
		std::vector<T> m_Data;
		std::mutex m_Mutex;
	};

	template<typename T>
	inline T& ListDataWrapper<T>::operator[](std::size_t index)
	{
		return m_Data[index];
	}

	template<typename T>
	inline const T& ListDataWrapper<T>::operator[](std::size_t index) const
	{
		return m_Data[index];
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
	inline std::vector<std::uint32_t> ListDataWrapper<T>::ids() const
	{
		std::set<std::uint32_t> ids;

		for (const auto& elem : m_Data)
		{
			const std::uint32_t _id = elem.id();
			if (!ids.contains(_id))
			{
				ids.insert(_id);
			}
		}

		std::vector<std::uint32_t> result(std::begin(ids), std::end(ids));
		return result;
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
		{
			m_Data.clear();
		}
		{
			std::scoped_lock sl(m_Mutex);
			m_Data = std::move(src);
		}
	}

	template<typename T>
	inline void ListDataWrapper<T>::sendUpdatePrices(int owner_id) const
	{
		if (m_Data.empty())
		{
			return;
		}

		auto& container = AppraisalContainer::Instance();
		for (const auto& elem : m_Data)
		{
			container.addInQueueIfNeed(UpdatePriceRecord{ owner_id, elem.id(), elem.m_EsiSettings });
		}
	}

	template<typename T>
	inline void ListDataWrapper<T>::sendUpdateImages(int owner_id) const
	{
		if (m_Data.empty())
		{
			return;
		}

		auto& container = BitmapContainer::Instance();
		for (const auto& elem : m_Data)
		{
			container.addInQueueIfNeed(UpdateBitmapRecord{ owner_id, elem.id(), BitmapSize::x16 });
		}

		container.setLastUpdateNow(owner_id);
	}

} // EVE::Industry

#endif // _EVEINDUSTRY_LISTDATAWRAPPER_HPP_