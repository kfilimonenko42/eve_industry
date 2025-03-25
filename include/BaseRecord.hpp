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

#ifndef _EVEINDUSTRY_BASERECORD_HPP_
#define _EVEINDUSTRY_BASERECORD_HPP_

#include <string>
#include <format>
#include <cstdint>
#include <wx/string.h>

namespace EVE::Industry
{

	class BaseRecord
	{
	public:
		BaseRecord() = default;
		BaseRecord(const std::string& name, const std::uint32_t id);
		BaseRecord(std::string&& name, const std::uint32_t id);
		virtual ~BaseRecord() = default;

		const std::string& name() const;
		wxString wxName() const;
		std::uint32_t id() const;
		virtual std::string toString() const;
		virtual wxString towxString() const;

	protected:
		std::string m_Name;
		std::uint32_t m_ID{};
	};

	struct BaseRecordSortByName
	{
		bool operator()(const BaseRecord& lhs, const BaseRecord& rhs)
		{
			return lhs.name() < rhs.name();
		}
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_BASERECORD_HPP_