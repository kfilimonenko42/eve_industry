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

#ifndef _ESI_SERTIFICATE_HPP_
#define _ESI_SERTIFICATE_HPP_

#include <boost/asio/ssl.hpp>
#include <filesystem>
#include <format>

namespace ESI 
{

    inline void loadCertificates(boost::asio::ssl::context& ctx)
    {
        const std::string chainfile = std::format("{}/assets/certs/esi-chain.pem", std::filesystem::current_path().string());
        ctx.load_verify_file(chainfile);
    }

} // namespace ESI

#endif // _ESI_SERTIFICATE_HPP_