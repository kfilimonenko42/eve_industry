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

#include "Logger.hpp"

Log::Logger::Logger(const std::string& fileName)
	: m_FileHandler(fileName)
{
}

Log::Logger& Log::Logger::Instance()
{
	static Log::Logger instance{ std::filesystem::current_path().string() + "/info.log" };
	return instance;
}

void Log::Logger::log(const Log::Level level, const std::string& message)
{
	m_FileHandler.write(
		std::format(std::locale(""), "{} ({:L}): {}\n",
			arrLevelStr.at(static_cast<int>(level)),
			std::chrono::system_clock::now(),
			message)
	);
}