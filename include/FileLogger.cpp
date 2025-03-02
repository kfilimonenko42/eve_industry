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

#include "FileLogger.hpp"

Log::FileLog::FileLog(const std::string& fileName, const size_t sizeBuffer)
	: m_File{ fileName, std::ios::app | std::ios::out }, m_BufferSize{ sizeBuffer }, m_Buffer(sizeBuffer)
{
	if (!m_File.is_open())
	{
		throw std::runtime_error("Can't open log file");
	}
}

Log::FileLog::~FileLog()
{
	flush();
}

void Log::FileLog::write(const std::string& str)
{
	std::scoped_lock sl(m_Mutex);

	const std::size_t _size = str.size();
	if (m_Offset + _size >= m_BufferSize)
	{
		flush();
	}

	std::copy(std::begin(str), std::end(str), std::begin(m_Buffer) + m_Offset);
	m_Offset += _size;
}

void Log::FileLog::flush()
{
	//std::scoped_lock sl(m_Mutex);

	if (m_Offset > 0)
	{
		m_File.write(m_Buffer.data(), m_Offset);
		m_Offset = 0;
	}
}
