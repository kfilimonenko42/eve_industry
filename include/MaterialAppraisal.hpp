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

#ifndef _EVEINDUSTRY_MATERIALAPPRAISAL_HPP_
#define _EVEINDUSTRY_MATERIALAPPRAISAL_HPP_

#include <cstdint>

#include "TypeRecord.hpp"
#include "EsiOrderSettings.hpp"

namespace EVE::Industry
{

	struct MaterialAppraisal
	{
		template<typename T>
		MaterialAppraisal(T&& type, const EsiOrderSettings& esiSettings);

		inline std::uint32_t id() const
		{
			return m_Type.id();
		}

		TypeRecord m_Type;
		EsiOrderSettings m_EsiSettings;
	};

	template<typename T>
	inline MaterialAppraisal::MaterialAppraisal(T&& type, const EsiOrderSettings& esiSettings)
		: m_Type{ std::forward<T>(type) }, m_EsiSettings{ esiSettings }
	{
	}

} // EVE::Industry

#endif // _EVEINDUSTRY_MATERIALAPPRAISAL_HPP_