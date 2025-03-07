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

#ifndef _EVEINDUSTRY_STRINGPARSER_V3_HPP_
#define _EVEINDUSTRY_STRINGPARSER_V3_HPP_

#include <string>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <regex>
#include <cstdint>

#include "IBaseStringParser.hpp"

namespace EVE::Industry
{

	class StringParser_v3 : public IBaseStringParser
	{
	public:
		StringParser_v3() = default;

		std::tuple<std::string, std::uint64_t> parse(const std::string& src) override;

	private:
		void check_from_assets(std::string& src) const;
		bool match_firstline(const std::string& src) const;
		bool match_left(const std::string& src) const;
		bool match_right(const std::string& src) const;
		
		std::tuple<std::string, std::uint64_t> do_parse_firstline(std::string& src);
		std::tuple<std::string, std::uint64_t> do_parse_left(std::string& src);
		std::tuple<std::string, std::uint64_t> do_parse_right(std::string& src);
		std::tuple<std::string, std::uint64_t> do_parse(std::string& src);
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_STRINGPARSER_V3_HPP_