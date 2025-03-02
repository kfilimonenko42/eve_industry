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

#include <wx/wx.h>

namespace EVE::Industry
{

	class BitmapContainer
	{
	public:
		using mwxBitmap = std::map<std::uint32_t, wxBitmap>;
		using mIDLine = std::map<std::uint32_t, std::size_t>;

		BitmapContainer() = default;
		~BitmapContainer();

		static BitmapContainer& Instance();

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
		mwxBitmap m_Containerx16;
		mwxBitmap m_Containerx32;

		std::mutex m_Mutex16;
		std::mutex m_Mutex32;
	};


} // EVE::Industry

#endif // _EVEINDUSTRY_BITMAPCONTAINER_HPP_