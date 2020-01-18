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
#ifndef __OCTO_OCTO_URI_URI_H_
#define __OCTO_OCTO_URI_URI_H_

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>

namespace octo {
namespace uri {
    /**
     * this uri class is based on the work of rhymu8354
     * (https://github.com/rhymu8354/)
     * 
     * repository: https://github.com/rhymu8354/Uri.git
     */
    class Uri {
    public:
        ~Uri() noexcept;
        Uri(const Uri& other);
        Uri(Uri&&) noexcept;
        Uri& operator=(const Uri& other);
        Uri& operator=(Uri&&);
    public:
        Uri();
        bool operator==(const Uri& other) const;
        bool operator!=(const Uri& other) const;
        bool parse(const std::string& rawUri);
        std::string getScheme() const;
        std::string getUserInfo() const;
        std::string getHost() const;
        std::vector< std::string > getPath() const;
        bool hasPort() const;
        uint16_t getPort() const;
        bool isRelativeRef() const;
        bool containsRelativePart() const;
        bool hasQuery() const;
        std::string getQuery() const;
        void normalizePath();
        Uri resolve(const Uri& ref) const;
        void setScheme(const std::string& scheme);
        void setUserInfo(const std::string& uinfo);
        void setHost(const std::string& host);
        void setPort(uint16_t port);
        void clearPort();
        void setPath(const std::vector< std::string >& path);
        void clearQuery();
        void setQuery(const std::string& query);
        void clearFragment();
        void setFragment(const std::string& frag);
        std::string generateUri() const;
    private:
        struct Impl;
        std::unique_ptr< Impl > impl_;
    };
} // namespace uri
} // namespace octo

#endif // __OCTO_OCTO_URI_URI_H_