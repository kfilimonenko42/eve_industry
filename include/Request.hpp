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

#ifndef _RESTAPI_REQUEST_HPP_
#define _RESTAPI_REQUEST_HPP_

#include <algorithm>
#include <utility>
#include <format>
#include <string>
#include <filesystem>
#include <memory>
#include <functional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>

#include "Logger.hpp"
#include "Response.hpp"

namespace RestAPI
{

    class Request
    {
    public:
        using Context = boost::asio::io_context;
        using Context_ssl = boost::asio::ssl::context;
        using Stream = boost::asio::ssl::stream<boost::beast::tcp_stream>;

        Request(
            const std::string& host,
            const std::string& port,
            std::function<void(boost::asio::ssl::context&)> add_cert,
            Context_ssl::method method = Context_ssl::tlsv12_client);

        RestAPI::Response get(const std::string& target);

    private:
        std::string m_Host;
        std::string m_Port;
        std::function<void(boost::asio::ssl::context&)> m_fAddCert;
        Context_ssl::method m_MethodSSL;
    };

} // namespace RestAPI

#endif // _RESTAPI_REQUEST_HPP_