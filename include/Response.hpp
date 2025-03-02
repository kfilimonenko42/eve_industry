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

#ifndef _RESTAPI_RESPONSE_HPP_
#define _RESTAPI_RESPONSE_HPP_

#include <algorithm>
#include <utility>
#include <format>
#include <string>
#include <filesystem>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>

#include "Logger.hpp"

namespace RestAPI
{

    class Response
    {
    public:
        explicit Response(bool successful = false)
            : m_Successful{ successful }
        {
        }

        Response(bool successful, std::string&& json_str)
            : m_Successful{ successful }, m_Result{ std::move(json_str) }
        {
        }

        bool m_Successful{};
        std::string m_Result;
    };

} // namespace RestAPI

#endif // _RESTAPI_RESPONSE_HPP_