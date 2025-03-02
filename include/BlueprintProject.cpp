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

#include "BlueprintProject.hpp"

EVE::Industry::BlueprintProject::BlueprintProject(
	const BlueprintRecord& bp, const SolarSystemRecord& solSystem, ME me, const std::uint64_t maxRunsPerJob)
	: m_Blueprint{ bp }, m_SolarSystem{ solSystem }, m_ME{ me }, m_MaxRunsPerJob{ maxRunsPerJob }
{
	check();
}

EVE::Industry::BlueprintProject::BlueprintProject(
	BlueprintRecord&& bp, SolarSystemRecord&& solSystem, ME me, const std::uint64_t maxRunsPerJob)
	: m_Blueprint{ std::move(bp) }, m_SolarSystem{ std::move(solSystem) }, m_ME{ me }, m_MaxRunsPerJob{ maxRunsPerJob }
{
	check();
}

std::uint32_t EVE::Industry::BlueprintProject::id() const
{
	return this->m_Blueprint.id();
}

void EVE::Industry::BlueprintProject::setSolarSystem(const SolarSystemRecord& solSystem)
{
	this->m_SolarSystem = solSystem;
}

void EVE::Industry::BlueprintProject::check()
{
	if (this->m_MaxRunsPerJob == 0)
	{
		this->m_MaxRunsPerJob = this->m_Blueprint.maxRunsPerJob();
	}

	if (this->m_ME.m_BpME == EVE::Assets::BlueprintME::ME_0)
	{
		this->m_ME.m_BpME = this->m_Blueprint.bpME();
	}

	if (this->m_ME.m_StructME == EVE::Assets::StructureME::ME_0)
	{
		this->m_ME.m_StructME = this->m_Blueprint.structME();
	}

	if (this->m_ME.m_RigME == EVE::Assets::RigME::NO_RIG)
	{
		this->m_ME.m_RigME = this->m_Blueprint.rigME();
	}
}
