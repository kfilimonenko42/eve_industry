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

#include "DecomposeBlueprints.hpp"
#include "Assets.hpp"

void EVE::Industry::DecomposeBlueprint::operator()(
	const BlueprintRecord& _source,
	std::vector<BlueprintProject>& _dst)
{
	MaterialsToBlueprints mattobps{};
	mattobps(
		_source.getIDsManufacturingMaterials(),
		_dst);
}

void EVE::Industry::MaterialsToBlueprints::operator()(
	const std::vector<std::uint32_t>& _source,
	std::vector<BlueprintProject>& _dst)
{;
	using bpME = EVE::Assets::BlueprintMaterialEfficiency;
	DecomposeBlueprint decbps{};

	for (const std::uint32_t type_id : _source)
	{
		TypeRecord type;
		try
		{
			type = TypeRecord{ type_id };
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
			continue;
		}

		if (type.bpID() == 0)
		{
			continue;
		}

		BlueprintRecord bp;
		try
		{
			bp = BlueprintRecord{ type.bpID() };
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
			continue;
		}

		auto ittrdst = std::find_if(std::begin(_dst), std::end(_dst),
			[&bp](const BlueprintProject& element)
			{
				return element.m_Blueprint.id() == bp.id();
			}
		);
		if (ittrdst != _dst.end())
		{
			continue;
		}

		_dst.emplace_back(bp, SolarSystemRecord{}, bpME{});
		decbps(bp, _dst);
	}
}
