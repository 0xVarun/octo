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
	bool has_scheme;
	std::string scheme;
    };

    Uri::Uri() : impl_(new Impl) {}

    bool Uri::parse(const std::string& raw) {
        size_t scheme_delimiter = raw.find(":");
	std::string rest;
	if (scheme_delimiter == std::string::npos) {
	    this->impl_->has_scheme = false;
	    rest = raw;
	} else {
	    this->impl_->has_scheme = true;
	    this->impl_->scheme = raw.substr(0, scheme_delimiter);
	    rest = raw.substr(scheme_delimiter + 1);
	}
    }

    bool Uri::has_scheme() const {
	return this->impl_->has_scheme;
    }

    std::string Uri::get_scheme() const {
	if (this->impl_->has_scheme) {
	    return this->impl_->scheme;
	}
	return "";
    }

    Uri::~Uri() = default;

} // namespace uri
} // namespace octo
