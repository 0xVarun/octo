/**
 * Copyright (C) 2020 varun
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
        std::string scheme;
        std::string host;
        std::string userInfo;
        bool hasPort = false;
        uint16_t port;
        std::vector< std::string > path;
        bool hasQuery = false;
        std::string  query;
        bool hasFragment = false;
        std::string fragment;
    };

    Uri::~Uri() noexcept {

    }

    Uri::Uri(const Uri& other) {

    }

    Uri::Uri(Uri&&) noexcept {

    }

    Uri& Uri::operator=(const Uri& other) {

    }

    Uri& Uri::operator=(Uri&&) {
        
    }

    Uri::Uri() : impl_(new Impl) {}

    bool Uri::operator==(const Uri& other) const {

    }

    bool Uri::operator!=(const Uri& other) const {

    }

    bool Uri::parse(const std::string& rawUri) {

    }

    std::string Uri::getScheme() const {
        return this->impl_->scheme;
    }

    std::string Uri::getUserInfo() const {
        return this->impl_->userInfo;
    }

    std::string Uri::getHost() const {
        return this->impl_->host;
    }

    std::vector< std::string > Uri::getPath() const {
        return this->impl_->path;
    }

    bool Uri::hasPort() const {
        return this->impl_->hasPort;
    }

    uint16_t Uri::getPort() const {
        return this->impl_->port;
    }

    bool Uri::isRelativeRef() const {

    }

    bool Uri::containsRelativePart() const {

    }

    bool Uri::hasQuery() const {
        this->impl_->hasQuery;
    }

    std::string Uri::getQuery() const {
        return this->impl_->query;
    }

    void Uri::normalizePath() {

    }

    Uri Uri::resolve(const Uri& ref) const {

    }

    void Uri::setScheme(const std::string& scheme) {
        this->impl_->scheme = scheme;
    }

    void Uri::setUserInfo(const std::string& uinfo) {
        this->impl_->userInfo = uinfo;
    }

    void Uri::setHost(const std::string& host) {
        this->impl_->host = host;
    }

    void Uri::setPort(uint16_t port) {
        this->impl_->hasPort = true;
        this->impl_->port = port;
    }

    void Uri::clearPort() {
        this->impl_->hasPort = false;
    }

    void Uri::setPath(const std::vector< std::string >& path) {
        this->impl_->path = path;
    }

    void Uri::clearQuery() {
        this->impl_->query.clear();
        this->impl_->query = false;
    }

    void Uri::setQuery(const std::string& query) {
        this->impl_->hasQuery = true;
        this->impl_->query = query;
    }

    void Uri::clearFragment() {
        this->impl_->fragment.clear();
        this->impl_->hasFragment = false;
    }

    void Uri::setFragment(const std::string& frag) {
        this->impl_->hasFragment = true;
        this->impl_->fragment = frag;
    }

    std::string Uri::generateUri() const {

    }

} // namespace uri
} // namesapce octo