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

#include "TradeRecord.hpp"

EVE::Industry::TradeRecord::TradeRecord(const std::uint64_t quanity)
	: m_Quantity{ quanity }
{
}

void EVE::Industry::TradeRecord::setQuantity(const std::uint64_t quantity)
{
	this->m_Quantity = quantity;
}

void EVE::Industry::TradeRecord::setVolume(const double volume)
{
	this->m_Volume = volume;
}

std::uint64_t EVE::Industry::TradeRecord::getQuantity() const
{
	return this->m_Quantity;
}

std::string EVE::Industry::TradeRecord::quantityToString() const
{
	return std::format(std::locale(""), "{:L}", getQuantity());
}

double EVE::Industry::TradeRecord::getVolume() const
{
	return this->m_Volume;
}

double EVE::Industry::TradeRecord::getVolumeTotal() const
{
	return getVolume() * getQuantity();
}

std::string EVE::Industry::TradeRecord::volumeTotalToString() const
{
	return std::format(std::locale(""), "{:.2Lf}", getVolumeTotal());
}
