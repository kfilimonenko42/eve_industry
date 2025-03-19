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

#ifndef _EVEASSETS_ORDER_HPP_
#define _EVEASSETS_ORDER_HPP_

#include <cstdint>
#include <string>

namespace EVE::Assets
{

	class Order
	{
	public:
		Order() = default;

		bool operator==(const Order& rhs) const
		{
			return this->m_Price == rhs.m_Price;
		}

		auto operator<=>(const Order& rhs) const
		{
			return this->m_Price <=> rhs.m_Price;
		}

	public:
		std::string m_Issued;
		std::string m_Range;
		double m_Price{};
		std::uint64_t m_ID{};
		std::uint32_t m_Duration{};
		std::uint32_t m_LocationID{};
		std::uint32_t m_SystemID{};
		std::uint32_t m_TypeID{};
		std::uint32_t m_MinVolume{};
		std::uint32_t m_VolumeRemain{};
		std::uint32_t m_VolumeTotal{};
		bool m_IsBuyOrder{};
	};

} // namespace EVE::Assets

#endif // _EVEASSETS_ORDER_HPP_