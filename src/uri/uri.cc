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

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#include <octo/uri/uri.h>

namespace octo {
namespace uri {

struct Uri::Impl {
  /**
   * this holds the scheme (protocol)
   * part of the uri if present
   */
  std::string scheme;

  /**
   * this flag indicates if the scheme (protocol)
   * part of the uri is present
   */
  bool has_scheme;

  /**
   * this holds the host part of
   * the uri if present (not relative)
   */
  std::string host;

  /**
   * this holds the port of the uri
   * if present
   */
  uint16_t port;

  /**
   * flag that indicates if the URI has a port
   * component, if false, port value will be
   * ignored
   */
  bool has_port;

  /**
   * this flag indicates if the
   */
  bool is_relative;

  /**
   * this hold the segments of path
   * in the URI
   */
  std::vector<std::string> path;

  /**
   * this is a helper method that parses the Scheme
   * part of the URI if present
   *
   * @param[in] uri
   *     uri is the unparsed URI that may contain
   *     the scheme element
   *
   * @param[in] rest
   *     rest holds the substring after the uri has
   *     been parsed for the scheme and the scheme
   *     is removed
   */
  bool parseScheme(const std::string& uri, std::string& rest) {
    size_t authority_path_start = uri.find("/");
    if (authority_path_start == std::string::npos) {
      authority_path_start = uri.length();
    }
    size_t scheme_delimiter = uri.substr(0, authority_path_start).find(":");
    if (scheme_delimiter == std::string::npos) {
      this->has_scheme = false;
      rest = uri;
    } else {
      this->has_scheme = true;
      this->scheme = uri.substr(0, scheme_delimiter);
      rest = uri.substr(scheme_delimiter + 1);
    }
    return true;
  }

  /**
   * this method parses the authority into its host
   * and port components if port is present otherwise
   * assume entire string is host
   *
   * @param[in] authority
   *     this contains the host:port path of the URI
   *     :port is optional, for http assume 80 and
   *     443 for https
   *
   * @return bool
   *     an indication, whether the parsing was
   *     successful
   */
  bool parseAuthority(std::string& authority) {
    size_t portDelimiter = authority.find(":");
    if (portDelimiter == std::string::npos) {
      this->has_port = false;
      this->host = authority;
    } else {
      this->has_port = true;
      this->host = authority.substr(0, portDelimiter);
      this->port = static_cast<uint16_t>(
          std::stoi(authority.substr(this->host.length() + 1)));
    }
    return true;
  }

  /**
   * this method splits the string into its path
   * component and authority component
   *
   * @param[in] authoriyWithPath
   *    this contains the authority and path
   *    which is not parsed
   *
   * @param[in] pathString
   *    this is where the path component
   *    of the uri is stored after the
   *    authority has been removed.
   */
  bool splitAuthorityAndPath(std::string& authrorityWithPath,
                             std::string& pathString) {
    if (authrorityWithPath.substr(0, 2) == "//") {
      authrorityWithPath = authrorityWithPath.substr(2);
      this->is_relative = false;
      size_t pathStart = authrorityWithPath.find("/");
      if (pathStart == std::string::npos) {
        pathStart = authrorityWithPath.length();
      }
      pathString = authrorityWithPath.substr(pathStart);
      std::string authority = authrorityWithPath.substr(0, pathStart);
      if (!parseAuthority(authority)) {
        return false;
      }
    } else {
      this->is_relative = true;
      this->has_port = false;
      pathString = authrorityWithPath;
    }
    return true;
  }

  /**
   * this method parses the path string into
   * a sequence of segments
   *
   * @param[in] pathString
   *     this holds the unparsed path string
   *     of the URI
   *
   * @param[in] rest
   *     this holds the query part and the fragment
   *     path of the URI if present
   */
  bool parsePath(std::string& pathString, std::string& rest) {
    this->path.clear();
    size_t qfDelimiter = pathString.find("?");
    if (qfDelimiter == std::string::npos) {
      qfDelimiter = pathString.length();
    }
    rest = pathString.substr(qfDelimiter + 1);
    pathString = pathString.substr(0, qfDelimiter);
    if (pathString == "/") {
      this->path.push_back("");
      pathString.clear();
    } else {
      for (;;) {
        size_t slashDelimiter = pathString.find("/");
        if (slashDelimiter == std::string::npos) {
          this->path.push_back(pathString);
          pathString.clear();
          break;
        } else {
          this->path.emplace_back(pathString.begin(),
                                  pathString.begin() + slashDelimiter);
          pathString = pathString.substr(slashDelimiter + 1);
        }
      }
    }
    return true;
  }
};

Uri::Uri() : impl_(new Impl) {}

bool Uri::parse(const std::string& raw) {
  std::string rest;
  if (!this->impl_->parseScheme(raw, rest)) {
    return false;
  }
  std::string pathString;
  if (!this->impl_->splitAuthorityAndPath(rest, pathString)) {
    return false;
  }
  std::string queryAndFragment;
  if (!this->impl_->parsePath(pathString, queryAndFragment)) {
    return false;
  }
  std::cout << queryAndFragment << std::endl;
  return true;
}

bool Uri::has_scheme() const { return this->impl_->has_scheme; }

std::string Uri::get_scheme() const {
  if (this->impl_->has_scheme) {
    return this->impl_->scheme;
  }
  return "";
}

std::vector<std::string> Uri::get_path() const { return this->impl_->path; }

Uri::~Uri() = default;

}  // namespace uri
}  // namespace octo
