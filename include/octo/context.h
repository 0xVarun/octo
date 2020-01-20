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

#ifndef __OCTO_CONTEXT_H_
#define __OCTO_CONTEXT_H_

#include <map>
#include <string>
#include <memory>
#include <chrono>
#include <stdint.h>

namespace octo {
class Context {
public:
    Context();
    ~Context();

    /**
     * Set the port to listen on
     * 
     * @param[in] port
     *      port is an uint16_t type
     *      that tells the server what port
     *      to listen on (default is 80)
     */
    void set_port(uint16_t port);

    /**
     * enable SSL model
     * 
     * @param[in] ssl
     *      ssl boolean tells the init modules
     *      to use ssl sockets only and reject
     *      all non-ssl connections 
     */
    void enable_ssl(bool ssl);

    /**
     * Set the sever timeout
     * 
     * @param[in] timeout
     *      sets the server request, response
     *      timeout in miliseconds
     */
    void set_timeout(std::chrono::milliseconds timeout);

    /**
     * Set the bind address
     * 
     * @param[in] addr
     *      addr specifes the address to bind
     *      the server to. (default localhost)
     */
    void set_bind_address(std::string addr);

    /**
     * Set the worker limit
     * 
     * @param[in] worker_limit
     *      this specifies background worker
     *      task executor limit, defaults to
     *      number of cpu cores
     */
    void set_worker_limit(unsigned int worker_limit);

    /**
     * Add to the default headers
     * 
     * @param[in] header
     *      this specifies the key part
     *      of the HTTP header
     * 
     * @param[in] value
     *      this specifes the value part
     *      of the HTTP header
     */
    void set_default_headers(std::string header, std::string value);

    /**
     * Add to the default headers
     * 
     * @param[in] header
     *      this hold a key-value pair of
     *      HTTP header name and HTTP 
     *      header value
     */
    void set_default_headers(std::pair< std::string ,std::string > header);

    /**
     * Append to the default headers
     * 
     * @param[in] headers
     *      this holds a map of headers
     */
    void set_default_headers(std::map< std::string, std::string > headers);
private:
    struct Impl;
    std::unique_ptr< Impl > impl_;
}; // class Context
} // namespace octo

#endif // __OCTO_CONTEXT_H_
