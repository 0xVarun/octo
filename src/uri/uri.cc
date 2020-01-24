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

#include <string>
#include <vector>
#include <stdint.h>

#include <octo/uri/uri.h>

namespace octo {
namespace uri {

    struct Uri::Impl {
        uint16_t port = static_cast<uint16_t>(0);
    };

    Uri::Uri() : impl_(new Impl) {}

    bool Uri::parse(const std::string& raw) {
        return true;
    }

    Uri::~Uri() = default;

} // namespace uri
} // namespace octo
