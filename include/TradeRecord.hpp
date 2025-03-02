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

#ifndef _EVEINDUSTRY_TRADERECORD_HPP_
#define _EVEINDUSTRY_TRADERECORD_HPP_

#include <string>
#include <format>
#include <cstdint>
#include <locale>

namespace EVE::Industry
{

	class TradeRecord
	{
	public:
		TradeRecord() = default;
		explicit TradeRecord(const std::uint64_t quanity);
		virtual ~TradeRecord() = default;

		void setQuantity(const std::uint64_t quantity);
		void setPriceBuy(const double price);
		void setPriceSell(const double price);
		void setVolume(const double volume);

		std::uint64_t getQuantity() const;
		std::string quantityToString() const;
		double getPriceBuy() const;
		double getPriceBuyTotal() const;
		std::string priceBuyToString() const;
		std::string priceBuyTotalToString() const;
		double getPriceSell() const;
		double getPriceSellTotal() const;
		std::string priceSellToString() const;
		std::string priceSellTotalToString() const;
		double getVolume() const;
		double getVolumeTotal() const;
		std::string volumeTotalToString() const;

	private:
		std::uint64_t m_Quantity{};
		double m_PriceBuy{};
		double m_PriceSell{};
		double m_Volume{};
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_TRADERECORD_HPP_