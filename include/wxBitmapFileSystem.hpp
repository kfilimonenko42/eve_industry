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

#ifndef _EVEINDUSTRY_BITMAPFILESYSTEM_HPP_
#define _EVEINDUSTRY_BITMAPFILESYSTEM_HPP_

#include <format>
#include <string>
#include <filesystem>
#include <wx/wx.h>

#include "Logger.hpp"

namespace EVE::Industry
{

	inline std::string bitmap_path_notfound_x16()
	{
		return std::format("{}/assets/icons/types/0_16.png", std::filesystem::current_path().string());
	}

	inline std::string bitmap_path_notfound_x32()
	{
		return std::format("{}/assets/icons/types/0_32.png", std::filesystem::current_path().string());
	}

	inline std::string bitmap_path_x16(const std::uint32_t id)
	{
		return std::format("{}/assets/icons/types/{}_16.png", std::filesystem::current_path().string(), id);
	}

	inline std::string bitmap_path_x32(const std::uint32_t id)
	{
		return std::format("{}/assets/icons/types/{}_32.png", std::filesystem::current_path().string(), id);
	}

	inline wxBitmap bitmap_x16(const std::uint32_t id)
	{
		const std::filesystem::path _path(bitmap_path_x16(id));
		if (std::filesystem::exists(_path))
		{
			Log::LOG_DEBUG("load bmp: " + _path.string());

			return wxBitmap(
				_path.string(),
				wxBITMAP_TYPE_PNG);
		}
		else
		{
			Log::LOG_DEBUG("Couldn't find bmp: " + _path.string());

			return wxBitmap(
				bitmap_path_notfound_x16(),
				wxBITMAP_TYPE_PNG);
		}
	}

	inline wxBitmap bitmap_x32(const std::uint32_t id)
	{
		const std::filesystem::path _path(bitmap_path_x32(id));
		if (std::filesystem::exists(_path))
		{
			Log::LOG_DEBUG("load bmp: " + _path.string());

			return wxBitmap(
				_path.string(),
				wxBITMAP_TYPE_PNG);
		}
		else
		{
			Log::LOG_DEBUG("Couldn't find bmp: " + _path.string());

			return wxBitmap(
				bitmap_path_notfound_x32(),
				wxBITMAP_TYPE_PNG);
		}
	}

} // EVE::Industry

#endif // _EVEINDUSTRY_BITMAPFILESYSTEM_HPP_