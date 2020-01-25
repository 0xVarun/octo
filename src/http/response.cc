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
#include <memory>
#include <vector>
#include <stdint.h>

#include <octo/http/response.h>

namespace octo {
namespace http {

    Response::Response() {
        this->headers = new std::map< std::string, std::string >;
        this->headers->insert(std::make_pair("X-Powered-By", "Octo/0.1.0"));
        this->payload = new std::vector< uint8_t >;
    }

    void Response::addHeader(std::pair<std::string, std::string> header) {
        this->headers->insert(header);
    }

    void Response::addPayload(std::string &payload) {
        this->payload->assign(payload.begin(), payload.end());
    }

    Response::~Response() {
        delete this->headers;
        delete this->payload;
    }

} // namespace http
} // namespace octo