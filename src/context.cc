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
#include <chrono>
#include <stdint.h>

#include <octo/context.h>

namespace octo {

    struct Context::Impl {
        uint16_t port = static_cast<uint16_t>(80);
        bool ssl = false;
        std::chrono::microseconds timeout = std::chrono::milliseconds(300);
        std::string bind_address = "localhost";
        unsigned int worker_limit = 5;
        std::map< std::string, std::string > *default_headers;
    };

    Context::Context() : impl_(new Impl) {
        this->impl_->default_headers = new std::map< std::string, std::string >();
    }

    void Context::set_port(uint16_t port) {
        this->impl_->port = port;
    }

    void Context::enable_ssl(bool ssl) {
        this->impl_->ssl = ssl;
    }

    void Context::set_timeout(std::chrono::milliseconds timeout) {
        this->impl_->timeout = timeout;
    }

    void Context::set_bind_address(std::string addr) {
        this->impl_->bind_address = addr;
    }

    void Context::set_worker_limit(unsigned int worker_limit) {
        this->impl_->worker_limit = worker_limit;
    }

    void Context::set_default_headers(std::string header, std::string value) {
        this->impl_->default_headers->insert({header, value});
    }

    void Context::set_default_headers(std::pair< std::string ,std::string > header) {
        this->impl_->default_headers->insert(header);
    }

    void Context::set_default_headers(std::map< std::string, std::string > headers) {
        this->impl_->default_headers->insert(headers.begin(), headers.end());
    }


    Context::~Context() {}

} // namespace octo