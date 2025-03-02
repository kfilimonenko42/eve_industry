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

#include "BitmapContainer.hpp"

#include "wxBitmapFileSystem.hpp"

EVE::Industry::BitmapContainer::~BitmapContainer()
{
	m_Containerx16.clear();
	m_Containerx32.clear();
}

EVE::Industry::BitmapContainer& EVE::Industry::BitmapContainer::Instance()
{
	static BitmapContainer instance{};
	return instance;
}

bool EVE::Industry::BitmapContainer::has16(const std::uint32_t id) const
{
	return m_Containerx16.contains(id);
}

bool EVE::Industry::BitmapContainer::update16(const std::uint32_t id)
{
	if (id == 0)
	{
		return false;
	}

	if (m_Containerx16.contains(id))
	{
		return true;
	}

	try
	{
		wxBitmap _bitmap = bitmap_x16(id);
		m_Containerx16.emplace(id, std::move(_bitmap));
	}
	catch (const std::runtime_error& ex)
	{
		Log::LOG_ERROR(std::format("Load bmp: {} ({})", id, ex.what()));
		return false;
	}

	return true;
}

void EVE::Industry::BitmapContainer::update16(const std::vector<std::uint32_t>& ids)
{
	std::scoped_lock<std::mutex> lock(m_Mutex16);

	for (const std::uint32_t _id : ids)
	{
		update16(_id);
	}
}

void EVE::Industry::BitmapContainer::get16(const std::uint32_t id, wxVector<wxBitmapBundle>& dst, mIDLine& idslink) const
{
	if (id == 0)
	{
		return;
	}

	if (!m_Containerx16.contains(id))
	{
		return;
	}

	if (idslink.contains(id))
	{
		return;
	}

	const std::size_t _size = dst.size();
	dst.push_back(m_Containerx16.at(id));
	idslink.emplace(id, _size);
}

void EVE::Industry::BitmapContainer::get16(const std::vector<std::uint32_t>& ids, wxVector<wxBitmapBundle>& dst, mIDLine& idslink) const
{
	dst.clear();
	dst.reserve(ids.size());
	idslink.clear();

	for (const std::uint32_t _id : ids)
	{
		get16(_id, dst, idslink);
	}
}

wxBitmapBundle EVE::Industry::BitmapContainer::get16(const std::uint32_t id) const
{
	if (m_Containerx16.contains(id))
	{
		return m_Containerx16.at(id);
	}

	return wxBitmapBundle();
}

bool EVE::Industry::BitmapContainer::has32(const std::uint32_t id) const
{
	return m_Containerx32.contains(id);
}

bool EVE::Industry::BitmapContainer::update32(const std::uint32_t id)
{
	if (id == 0)
	{
		return false;
	}

	if (m_Containerx32.contains(id))
	{
		return true;
	}

	try
	{
		wxBitmap _bitmap = bitmap_x32(id);
		m_Containerx32.emplace(id, std::move(_bitmap));
	}
	catch (const std::runtime_error& ex)
	{
		Log::LOG_ERROR(std::format("Load bmp: {} ({})", id, ex.what()));
		return false;
	}

	return true;
}

void EVE::Industry::BitmapContainer::update32(const std::vector<std::uint32_t>& ids)
{
	std::scoped_lock<std::mutex> lock(m_Mutex32);

	for (const std::uint32_t _id : ids)
	{
		update32(_id);
	}
}

void EVE::Industry::BitmapContainer::get32(const std::uint32_t id, wxVector<wxBitmapBundle>& dst, mIDLine& idslink) const
{
	if (id == 0)
	{
		return;
	}

	if (!m_Containerx32.contains(id))
	{
		return;
	}

	if (idslink.contains(id))
	{
		return;
	}

	const std::size_t _size = dst.size();
	dst.push_back(m_Containerx32.at(id));
	idslink.emplace(id, _size);
}

void EVE::Industry::BitmapContainer::get32(const std::vector<std::uint32_t>& ids, wxVector<wxBitmapBundle>& dst, mIDLine& idslink) const
{
	dst.clear();
	dst.reserve(ids.size());
	idslink.clear();

	for (const std::uint32_t _id : ids)
	{
		get32(ids, dst, idslink);
	}
}

wxBitmapBundle EVE::Industry::BitmapContainer::get32(const std::uint32_t id) const
{
	if (m_Containerx32.contains(id))
	{
		return m_Containerx32.at(id);
	}

	return wxBitmapBundle();
}