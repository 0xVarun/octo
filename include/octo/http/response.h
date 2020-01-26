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

#ifndef __OCTO_RESPONSE_H_
#define __OCTO_RESPONSE_H_

#include <string>
#include <vector>
#include <stdint.h>
#include <map>

namespace octo {
namespace http {
    struct Response {
    public:
        /**
         * this stores the HTTP headers that
         * will be part of the response
         *
         * @note this will contain a few
         * headers already. Please check
         * the API doc for default headers
         */
        std::map< std::string, std::string > headers;

        /**
         * this stores the raw byte by byte
         * response data (payload)
         */
        std::vector< uint8_t > payload;

        /**
         * this stores an indication of
         * whether the response is valid
         * or not
         */
        bool valid;

        /**
         * this stores the numeric status
         * code to the corresponding request
         */
        unsigned int statusCode;

        /**
         * this stores the string representation
         * status code to the corresponding request
         */
        std::string statusPhrase;
    public:
        Response();
        ~Response();

        /**
         * this function adds new header pair
         * to  the existing response headers
         * @param header
         *     key-value pair of header name and
         *     header value
         */
        void addHeader(std::pair< std::string, std::string > header);

        /**
         * this function takes in a string
         * and converts it into a vector of
         * unsigned int of 8 bits
         * @param payload
         *     string representation of
         *     the data to be sent
         */
        void addPayload(std::string& payload);

        /**
         * this function generate a proper
         * HTTP response message with appropriate
         * status, headers and body
         * @return
         */
        std::string serialize() const;

    }; // struct Response
}
} // namespace octo

#endif // __OCTO_RESPONSE_H
