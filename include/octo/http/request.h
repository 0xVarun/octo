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

#ifndef __OCTO_REQUEST_H_
#define __OCTO_REQUEST_H_

#include <memory>
#include <string>


namespace octo {
namespace http {
    class Request {
    public: // public function
        Request();
        ~Request();

        enum class Method {
            GET,
            POST,
            PUT,
            PATCH,
            DELETE,
            INVALID
        };

        /**
         * this method parses raw HTTP message
         * into its separate components
         * 
         * @param[in] raw
         *      this represents the raw HTTP
         *      message
         * 
         * @return true 
         * @return false 
         */
        bool parse_http_request(std::string& raw);

        /**
         * Get the method of the Request
         * 
         * @return std::string 
         */
        std::string get_method() const;

        /**
         * Get the path of the Request
         * 
         * @return std::string 
         */
        std::string get_path() const;

        /**
         * Get the http verion of the Request
         * 
         * @return std::string 
         */
        std::string get_http_verion() const;

        /**
         * Get the header from the Request
         * 
         * @param header header key
         * @return std::string 
         */
        std::string get_header(std::string header) const;
    private: // private function
        bool parse_request_line(std::string& req_line);
        bool parse_headers(std::string& payload);
        void print_headers() const;
    private: // private properties
        struct Impl;
        std::unique_ptr< Impl > impl_;
    }; // class Request
} // namespace http
} // namespace octo

#endif // __OCTO_REQUEST_H_