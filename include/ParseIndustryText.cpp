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

#include "ParseIndustryText.hpp"
#include "Assets.hpp"

void EVE::Industry::ParseIndustryText::operator()(
	std::unique_ptr<IBaseStringParser> _parser, 
	const std::vector<std::string>& _str_parse, 
	std::unordered_map<std::uint32_t, std::uint64_t>& _dst,
	const int multiplyBy)
{

	const Assets& assets = Assets::Instance();

	for (const auto& _s : _str_parse)
	{

		auto [name, count] = _parser->parse(_s);
		if (name.empty())
		{
			continue;
		}

		auto [found, type] = assets.m_TypesContainer.element(name);
		if (!found)
		{
			continue;
		}

		const std::uint64_t tmp_count = count * multiplyBy;
		_dst[type->m_ID] += tmp_count;

	}

}

void EVE::Industry::ParseIndustryText::operator()(
	std::unique_ptr<IBaseStringParser> _parser,
	const std::vector<std::string>& _str_parse,
	std::vector<EVE::Assets::Material>& _dst,
	const int multiplyBy)
{

	const Assets& assets = Assets::Instance();

	for (const auto& _s : _str_parse)
	{

		auto [name, count] = _parser->parse(_s);
		if (name.empty())
		{
			continue;
		}

		auto [found, type] = assets.m_TypesContainer.element(name);
		const std::uint64_t tmp_count = count * multiplyBy;
		if (!found)
		{
			continue;
		}

		_dst.emplace_back(type->m_ID, tmp_count);

	}

}

void EVE::Industry::ParseIndustryText::operator()(
	std::unique_ptr<IBaseStringParser> _parser,
	const std::vector<std::string>& _str_parse,
	std::vector<MaterialProject>& _dst,
	const int multiplyBy)
{
	const Assets& assets = Assets::Instance();

	for (const auto& _s : _str_parse)
	{

		auto [name, count] = _parser->parse(_s);
		if (name.empty())
		{
			continue;
		}

		auto [found, type] = assets.m_TypesContainer.element(name);
		if (!found)
		{
			continue;
		}

		const std::uint32_t type_id = type->m_ID;
		auto ittr = std::find_if(std::begin(_dst), std::end(_dst),
			[type_id](const MaterialProject& elem)
			{
				return elem.m_Type.id() == type_id;
			});

		const std::uint64_t tmp_count = count * multiplyBy;
		if (ittr != std::end(_dst))
		{
			ittr->add(tmp_count);
		}
		else
		{
			_dst.emplace_back(TypeRecord{ type }, tmp_count);
		}
	}

}