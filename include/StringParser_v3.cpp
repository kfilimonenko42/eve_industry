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

#include "StringParser_v3.hpp"
#include "StringTools.hpp"

std::tuple<std::string, std::uint64_t> EVE::Industry::StringParser_v3::parse(const std::string& src)
{
	std::string _tmp_str(src);
	trim_lr(_tmp_str);

	if (!_tmp_str.empty())
	{

		if (match_firstline(_tmp_str))
		{
			return do_parse_firstline(_tmp_str);
		}
		else if (match_right(_tmp_str))
		{
			return do_parse_right(_tmp_str);
		}
		else if (match_left(_tmp_str))
		{
			return do_parse_left(_tmp_str);
		}
		else
		{
			// ?
			return do_parse(_tmp_str);
		}

	}

	return std::make_tuple(std::string(), 0);
}

bool EVE::Industry::StringParser_v3::match_firstline(const std::string& src) const
{
	return (src.at(0) == '[' && src.back() == ']');
}

bool EVE::Industry::StringParser_v3::match_left(const std::string& src) const
{
	const std::regex base_regex_1("^\\d+x");
	const std::regex base_regex_2("^\\d+\\s+");

	std::smatch base_match_1;
	std::smatch base_match_2;
	return (std::regex_search(src, base_match_1, base_regex_1) || std::regex_search(src, base_match_2, base_regex_2));
}

bool EVE::Industry::StringParser_v3::match_right(const std::string& src) const
{
	const std::regex base_regex_1("\\s+x\\d+$");
	const std::regex base_regex_2("\\s+\\d+$");

	std::smatch base_match_1;
	std::smatch base_match_2;
	return (std::regex_search(src, base_match_1, base_regex_1) || std::regex_search(src, base_match_2, base_regex_2));
}

std::tuple<std::string, std::uint64_t> EVE::Industry::StringParser_v3::do_parse_firstline(std::string& src)
{
	const auto ittr_comma = std::find(src.begin(), src.end(), ',');
	if (ittr_comma != src.end())
	{
		const auto distance = std::distance(src.begin() + 1, ittr_comma);
		return std::make_tuple(src.substr(1, distance), 1);
	}
	else if (src.back() == ']')
	{
		const auto distance = std::distance(src.cbegin() + 1, src.cend() - 1);
		return std::make_tuple(src.substr(1, distance), 1);
	}

	return std::make_tuple(std::string(), 0);
}

std::tuple<std::string, std::uint64_t> EVE::Industry::StringParser_v3::do_parse_left(std::string& src)
{
	auto it_begin = src.begin();
	auto it_end = src.end();

	std::uint64_t out_count{};
	for (; it_begin != it_end; ++it_begin)
	{
		auto symbol = *it_begin;
		if (symbol >= 48 && symbol <= 57)
		{
			out_count *= 10;
			out_count += (static_cast<int>(symbol) - 48);
		}
		else
		{
			break;
		}
	}

	if (it_begin != it_end && (*it_begin == 'x' || *it_begin == 'X'))
	{
		++it_begin;
	}

	const auto start = std::distance(src.begin(), it_begin);
	const auto distance = std::distance(it_begin, it_end);
	std::string out_string = src.substr(start, distance);
	trim_lr(out_string);

	return std::make_tuple(out_string, out_count);
}

std::tuple<std::string, std::uint64_t> EVE::Industry::StringParser_v3::do_parse_right(std::string& src)
{
	auto it_begin = src.rbegin();
	auto it_end = src.rend();

	std::uint64_t index{ 1 };
	std::uint64_t out_count{};
	for (; it_begin != it_end; ++it_begin)
	{
		auto symbol = *it_begin;
		if (symbol >= 48 && symbol <= 57)
		{
			out_count = (static_cast<int>(symbol) - 48) * index + out_count;
			index *= 10;
		}
		else
		{
			break;
		}
	}

	if (it_begin != it_end && (*it_begin == 'x' || *it_begin == 'X'))
	{
		++it_begin;
	}

	const auto distance = std::distance(src.begin(), it_begin.base());
	std::string out_string = src.substr(0, distance);
	trim_lr(out_string);

	return std::make_tuple(out_string, out_count);
}

// ?
std::tuple<std::string, std::uint64_t> EVE::Industry::StringParser_v3::do_parse(std::string& src)
{
	const auto ittr_comma = std::find(src.begin(), src.end(), ',');
	if (ittr_comma != src.end())
	{
		const auto distance = std::distance(src.begin(), ittr_comma);
		return std::make_tuple(src.substr(0, distance), 1);
	}

	return std::make_tuple(src, 1);
}
