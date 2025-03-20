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

#ifndef _ESI_HPP_
#define _ESI_HPP_

#include <algorithm>
#include <utility>
#include <format>
#include <string>
#include <functional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>

#include "Request.hpp"
#include "Response.hpp"
#include "ESI_certificate.hpp"
#include "Logger.hpp"

namespace ESI
{

    constexpr char HOST[] = "esi.evetech.net";
    constexpr char PORT[] = "443";

    inline RestAPI::Response get(const std::string& target)
    {
        try
        {
            std::function<void(boost::asio::ssl::context&)> add_cerf = &ESI::loadCertificates;
            RestAPI::Request request{ HOST, PORT, add_cerf, boost::asio::ssl::context::tlsv12_client };
            return request.get(target);
        }
        catch (const std::runtime_error& er)
        {
            Log::LOG_ERROR(std::format("esi get: {}", er.what()));
        }

        return RestAPI::Response();
    }

    inline RestAPI::Response getOrders(
        const std::uint32_t regionID,
        const std::uint32_t typeID)
    {
        const std::string target = std::format("/latest/markets/{}/orders/?datasource=tranquility&order_type=all&page=1&type_id={}", regionID, typeID);
        return get(target);
    }

    inline RestAPI::Response getType(
        const std::uint32_t typeID)
    {
        const std::string target = std::format("/latest/universe/types/{}/?datasource=tranquility&language=en", typeID);
        return get(target);
    }

    inline RestAPI::Response getSystemsCostIndicies()
    {
        const std::string target = std::format("/latest/industry/systems/?datasource=tranquility");
        return get(target);
    }

} // namespace ESI

#endif // _ESI_HPP_