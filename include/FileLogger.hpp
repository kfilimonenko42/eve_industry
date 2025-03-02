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

#ifndef _FILELOG_HPP_
#define _FILELOG_HPP_

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <mutex>
#include <algorithm>

namespace Log
{

	class FileLog
	{
	public:
		FileLog(const std::string& fileName, const std::size_t sizeBuffer = 1024);
		~FileLog();

		FileLog(const Log::FileLog&) = delete;
		Log::FileLog& operator=(const Log::FileLog&) = delete;
		FileLog(Log::FileLog&&) = delete;
		Log::FileLog& operator=(Log::FileLog&&) = delete;

		void write(const std::string& str);
		void flush();

	private:
		std::ofstream m_File;
		std::size_t m_BufferSize{};
		std::vector<char> m_Buffer;
		std::size_t m_Offset{};
		std::mutex m_Mutex;
	};

} // namespace Logger

#endif // _LOG_HPP_