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
#include <string.h>
#include <sstream>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include <octo/uri/uri.h>
#include <octo/http/request.h>

#define CRLF "\r\n"
#define SPACE " "

namespace {
    std::string PAYLOAD_DELIMITER("\r\n\r\n");
}

namespace octo {
namespace  http {

    std::map< Request::Method, std::string > method_str = {
        { Request::Method::GET,     "GET"       },
        { Request::Method::POST,    "POST"      },
        { Request::Method::PUT,     "PUT"       },
        { Request::Method::PATCH,   "PATCH"     },
        { Request::Method::DELETE,  "DELETE"    },
        { Request::Method::INVALID, "INVALID"   },
    };

    Request::Method parse_method(const std::string& method) {
        if (method == "GET" || method == "get") {
            return Request::Method::GET;
        } else if (method == "POST" || method == "post") {
            return Request::Method::POST;
        } else if (method == "PUT" || method == "put") {
            return Request::Method::PUT;
        } else if (method == "PATCH" || method == "patch") {
            return Request::Method::PATCH;
        } else if (method == "DELETE" || method == "delete") {
            return Request::Method::DELETE;
        } else {
            return Request::Method::INVALID;
        }
    }

    Request::Request() {}
    
    bool Request::parse_http_request(std::string& raw) {
        size_t request_line_size = raw.find_first_of(CRLF);
        if (request_line_size == std::string::npos) {
            return false;
        }
        std::string req_line = raw.substr(0, request_line_size);
        bool valid_request_line =this->parse_request_line(req_line);
        if (!valid_request_line) {
            return false;
        }
        std::string rest = raw.substr(request_line_size + 2);
        this->parse_headers(rest);

        // checking if the Content-Length equals Payload size
        std::string contentLength = this->get_header("Content-Length");
        if (contentLength.length() == 0) {
            return false;
        }
        size_t payloadSize = this->payload.size();
        size_t reportSize = static_cast<size_t>(std::stoi(contentLength));
        if (payloadSize != reportSize) {
            return false;
        }

	// need to prepare route dispatcher
        return true;
    }

    bool Request::parse_request_line(std::string& req_line) {
        // "GET /foo/bar HTTP/1.1"

        // parses HTTP Method
        size_t delimiter = req_line.find(SPACE);
        if (delimiter == std::string::npos) {
            return false;
        }
        this->method = parse_method(req_line.substr(0, delimiter));
        if (this->method == Method::INVALID) {
            return false;
        }

        // parses HTTP Resource
        std::string rest = req_line.substr(delimiter + 1);
        delimiter = rest.find(SPACE);
        if (delimiter == std::string::npos) {
            return false;
        }

        this->path.parse(rest.substr(0, delimiter));
        rest = rest.substr(delimiter + 1);

        // parses HTTP version
        this->http_version = rest.substr(0, rest.length());

        return true;
    }

    bool Request::parse_headers(std::string& payload) {
        size_t delimiter = payload.find(PAYLOAD_DELIMITER);
        if (delimiter == std::string::npos) {
            return false;
        }
        std::string headers = payload.substr(0, delimiter);
        std::string data = payload.substr(delimiter + PAYLOAD_DELIMITER.length());
        this->payload.assign(data.begin(), data.end());
        std::vector< std::string > header_lines;
        boost::split(header_lines, headers, boost::is_any_of("\r\n"));
        for(std::string header: header_lines) {
            if (header.length () > 0) {
                size_t kv = header.find(":");
                if (kv == std::string::npos) {
                    std::cout << header << std::endl;
                    return false;
                }
                std::string key = header.substr(0, kv);
                boost::algorithm::trim(key);
                std::string value = header.substr(kv + 1);
                boost::algorithm::trim(value);
                this->headers.emplace(std::make_pair(key, value));
            }
        }
    }



    std::string Request::get_method() const {
        return method_str[this->method];
    }
    
    std::string Request::get_path() const {
        std::ostringstream ss;
        ss << this->path;
        return ss.str();
    }

    std::string Request::get_http_verion() const {
        return this->http_version;
    }

    std::string Request::get_header(std::string header) const {
        if(this->headers.find(header) == this->headers.end()) {
            return "";
        } else {
            return this->headers.at(header);
        }
    }

}
}