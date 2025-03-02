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

#ifndef _EVEINDUSTRY_TYPERECORD_HPP_
#define _EVEINDUSTRY_TYPERECORD_HPP_

#include <string>
#include <format>
#include <cstdint>
#include <stdexcept>

#include "Assets.hpp"
#include "Type.hpp"
#include "BaseRecord.hpp"
#include "TradeRecord.hpp"

namespace EVE::Industry
{

	class TypeRecord : public BaseRecord, public TradeRecord
	{
	public:
		using Type = const EVE::Assets::Type*;

		TypeRecord() = default;
		TypeRecord(const std::uint32_t id);
		TypeRecord(Type type);
		~TypeRecord() override = default;

		const BaseRecord& group() const;
		std::uint32_t bpID() const;
		const std::string& description() const;

	private:
		void setValues(Type type);

	private:
		BaseRecord m_Group;
		std::string m_Description;
		std::uint32_t m_BlueprintID{};
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_TYPERECORD_HPP_