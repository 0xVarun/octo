/**
 * Copyright (C) 2020 Varun Tewari
 *
 * This file is part of octo.
 *
 * octo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * octo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with octo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <map>
#include <string>
#include <vector>
#include <sstream>

#include <octo/http/response.h>

#include <stout/uuid.hpp>

namespace octo {
namespace http {

    std::string CRLF("\r\n");

    Response::Response() {
        this->headers.insert(std::make_pair("Server", "Octo/0.1.0"));
        this->headers.insert(std::make_pair("x-octo-debug", UUID::random().toString()));
    }

    void Response::addHeader(std::pair<std::string, std::string> header) {
        this->headers.insert(header);
    }

    void Response::addPayload(std::string &payload) {
        this->payload.assign(payload.begin(), payload.end());
    }

    std::string Response::serialize() const {
        std::stringstream ss;
        ss << "HTTP/1.1";
        ss << " " << this->statusCode;
        ss << " " << this->statusPhrase << CRLF;
        std::map< std::string, std::string > localHeaders(this->headers.begin(), this->headers.end());
        std::map< std::string, std::string >::iterator it;
        for (it = localHeaders.begin(); it != localHeaders.end(); ++it) {
            ss << it->first  << ": " << it->second << CRLF;
        }
        ss << "Content-Length: " << this->payload.size() << CRLF;
        ss << CRLF;
        for(uint8_t item: this->payload) {
            ss << item;
        }
        return ss.str();
    }

    Response::~Response() = default;

} // namespace http
} // namespace octo