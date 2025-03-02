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

#include "JsonHelper.hpp"

JsonHelper::JsonHelper(std::string fileName) 
	: m_FileName{ std::move(fileName) }
{
}

bool JsonHelper::load(nlohmann::json &result)
{
	if (m_FileName.empty())
		return false;

	try
	{
		StringFileHelper fh(m_FileName);
		result = nlohmann::json::parse(fh.get());
	}
	catch (const std::runtime_error& ex)
	{
		Log::LOG_ERROR(ex.what());
		return false;
	}

	return true;
}

bool JsonHelper::save(const nlohmann::json &result)
{
	if (m_FileName.empty())
		return false;

	try
	{
		std::ofstream stream(m_FileName);
		stream << std::setw(4) << result << std::endl;
	}
	catch (const std::runtime_error& ex)
	{
		Log::LOG_ERROR(std::format("Couldn't save file {}. ({})", m_FileName, ex.what()));
		return false;
	}

	return true;
}
