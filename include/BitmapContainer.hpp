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

#ifndef _EVEINDUSTRY_BITMAPCONTAINER_HPP_
#define _EVEINDUSTRY_BITMAPCONTAINER_HPP_

#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <mutex>
#include <cassert>
#include <set>
#include <functional>
#include <wx/wx.h>

#include "UpdateContainerThread.hpp"
#include "AppraisalContainer.hpp"

namespace EVE::Industry
{

	enum class BitmapSize
	{
		x16,
		x32
	};

	struct UpdateBitmapRecord
	{
		UpdateBitmapRecord(int owner_id, std::uint32_t type_id, BitmapSize size)
			: m_OwnerId{ owner_id }, m_TypeId{ type_id }, m_Size{ size }
		{
		}

		int m_OwnerId{};
		std::uint32_t m_TypeId{};
		BitmapSize m_Size;
	};

	bool thread_bitmap_check(const UpdateBitmapRecord& updRecord);

	class BitmapContainer
	{
	public:
		using mwxBitmap = std::map<std::uint32_t, wxBitmap>;
		using mIDLine = std::map<std::uint32_t, std::size_t>;
		// set([type_id])
		using setQueue = std::set<std::uint32_t>;
		// update thread
		using updThread = UpdateContainerThread<UpdateBitmapRecord>;

		BitmapContainer() = default;
		~BitmapContainer();

		static BitmapContainer& Instance();

		void addInQueueIfNeed(const UpdateBitmapRecord& updRecord);
		bool check(const UpdateBitmapRecord& updRecord);
		time_point lastUpdate(int owner_id);
		void setLastUpdateNow(int owner_id);

		bool has16(const std::uint32_t id) const;
		bool update16(const std::uint32_t id);
		void update16(const std::vector<std::uint32_t>& ids);
		wxBitmapBundle get16(const std::uint32_t id) const;
		void get16(const std::uint32_t id, wxVector<wxBitmapBundle>& dst, mIDLine& idslink) const;
		void get16(const std::vector<std::uint32_t>& ids, wxVector<wxBitmapBundle>& dst, mIDLine& idslink) const;

		bool has32(const std::uint32_t id) const;
		bool update32(const std::uint32_t id);
		void update32(const std::vector<std::uint32_t>& ids);
		wxBitmapBundle get32(const std::uint32_t id) const;
		void get32(const std::uint32_t id, wxVector<wxBitmapBundle>& dst, mIDLine& idslink) const;
		void get32(const std::vector<std::uint32_t>& ids, wxVector<wxBitmapBundle>& dst, mIDLine& idslink) const;

	private:
		bool do_check(const UpdateBitmapRecord& updRecord);
		bool needUpdate(const UpdateBitmapRecord& updRecord) const;
		bool inQueue(const UpdateBitmapRecord& updRecord) const;
		void addInQueue(const UpdateBitmapRecord& updRecord);

	private:
		mwxBitmap m_Containerx16;
		std::mutex m_Mutex16;
		setQueue m_InQueuex16;

		mwxBitmap m_Containerx32;
		std::mutex m_Mutex32;
		setQueue m_InQueuex32;

		std::function<bool(const UpdateBitmapRecord&)> checkBitmapFunc = thread_bitmap_check;
		updThread m_UpdThread{ checkBitmapFunc };
	};

	inline bool bitmapUpdOwner(int owner_id, time_point last)
	{
		auto& container = BitmapContainer::Instance();
		time_point time = container.lastUpdate(owner_id);
		return time > last;
	}

} // EVE::Industry

#endif // _EVEINDUSTRY_BITMAPCONTAINER_HPP_