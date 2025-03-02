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

#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <string>
#include <format>
#include <array>
#include <filesystem>
#include <chrono>

#include "FileLogger.hpp"

namespace Log
{

	enum class Level
	{
		MESSAGE_INFO = 0,
		MESSAGE_DEBUG = 1,
		MESSAGE_ERROR = 2
	};

	static const std::array<std::string, 3> arrLevelStr = {
		"INFO",
		"DEBUG",
		"ERROR"
	};

	class Logger
	{
	public:
		Logger(const std::string& fileName);
		static Log::Logger& Instance();
		void log(const Log::Level level, const std::string& message);

	private:
		Log::FileLog m_FileHandler;
	};

	inline void LOG_INFO(const std::string& message)
	{
		Log::Logger::Instance().log(Log::Level::MESSAGE_INFO, message);
	}

	inline void LOG_DEBUG(const std::string& message)
	{
#if _DEBUG
		Log::Logger::Instance().log(Log::Level::MESSAGE_DEBUG, message);
#endif
	}

	inline void LOG_ERROR(const std::string& message)
	{
		Log::Logger::Instance().log(Log::Level::MESSAGE_ERROR, message);
	}

} // namespace Logger

#endif // _LOG_HPP_