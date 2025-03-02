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

#include "Request.hpp"

RestAPI::Request::Request(
    const std::string& host,
    const std::string& port,
    std::function<void(boost::asio::ssl::context&)> add_cert,
    Context_ssl::method method)
    : m_Host{ host }, m_Port{ port }, m_fAddCert{ add_cert }, m_MethodSSL{ method }
{
}

RestAPI::Response RestAPI::Request::get(const std::string& target)
{
    Context context;
    Context_ssl contextSSL{ m_MethodSSL };

    if (m_fAddCert)
    {
        m_fAddCert(contextSSL);
    }

    contextSSL.set_default_verify_paths();
    contextSSL.set_verify_mode(boost::asio::ssl::verify_none);

    boost::asio::ip::tcp::resolver resolver(context);
    Stream stream(context, contextSSL);

    if (!SSL_set_tlsext_host_name(stream.native_handle(), m_Host.c_str()))
    {
        boost::beast::error_code ec{ static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category() };
        throw boost::beast::system_error{ ec };
    }

    auto const results = resolver.resolve(m_Host, m_Port);

    boost::beast::get_lowest_layer(stream).connect(results);
    stream.handshake(boost::asio::ssl::stream_base::client);

    boost::beast::http::request<boost::beast::http::string_body> req{ boost::beast::http::verb::get, target, 11 };
    req.set(boost::beast::http::field::host, m_Host);
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    boost::beast::http::write(stream, req);

    boost::beast::flat_buffer buffer;
    boost::beast::http::response<boost::beast::http::string_body> res;
    boost::beast::http::read(stream, buffer, res);

    boost::system::error_code err;
    stream.shutdown(err);

    int _code = res.result_int();
    if (_code == 200)
    {
        std::string _s = res.body();
        return RestAPI::Response{ true, std::move(_s) };
    }

    return RestAPI::Response{};
}
