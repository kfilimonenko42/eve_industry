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

#include "VectorStrToTypeIndustry.hpp"
#include "ParseIndustryText.hpp"
#include "StringParser_v3.hpp"
#include "Assets.hpp"

void EVE::Industry::VectorStrToTypeIndustry::operator()(
	const std::vector<std::string>& source,
	std::unordered_map<std::uint32_t, std::uint64_t>& dst)
{
	ParseIndustryText parser{};
	parser(
		std::make_unique<StringParser_v3>(),
		source,
		dst
	);
}

void EVE::Industry::VectorStrToTypeIndustry::operator()(
	const std::vector<std::string>& source,
	std::vector<EVE::Assets::Material>& dst)
{
	ParseIndustryText parser{};
	parser(
		std::make_unique<StringParser_v3>(),
		source,
		dst
	);
}

void EVE::Industry::VectorStrToTypeIndustry::operator()(
	const std::vector<std::string>& source,
	std::vector<MaterialProject>& dst)
{
	ParseIndustryText parser{};
	parser(
		std::make_unique<StringParser_v3>(),
		source,
		dst
	);
}