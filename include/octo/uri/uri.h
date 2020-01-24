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

#ifndef __OCTO_URI_H_
#define __OCTO_URI_H_

#include <string>
#include <memory>
#include <stdint.h>

namespace octo {
namespace uri {
    class Uri {
    public:
        ~Uri();
    public:
        Uri();

        // public methods
        // bool operator==(const Uri& other) const;
        // bool operator!=(const Uri& other) const;
        // bool parse(const std::string& raw);
        bool parse(const std::string& raw);
        bool has_scheme() const;
        std::string get_scheme() const;
        // std::string get_host() const;
        // bool has_port() const;
        // uint16_t get_port() const;
        // bool is_relative() const;
    private:
        struct Impl;
        std::unique_ptr< Impl > impl_;
    }; // class Uri
} // namespace uri

} // namespace octo


#endif // __OCTO_URI_H_
