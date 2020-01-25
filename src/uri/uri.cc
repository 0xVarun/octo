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
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdint.h>

#include <octo/uri/uri.h>

namespace octo {
namespace uri {

struct Uri::Impl {
  /**
   * this stores the scheme (protocol)
   * part of the uri if present
   */
  std::string protocol;

  /**
   * this flag indicates if the scheme (protocol)
   * part of the uri is present
   */
  bool hasProtocol;

  /**
   * this stores the host part of
   * the uri if present (not relative)
   */
  std::string host;

  /**
   * this stores the port of the uri
   * if present
   */
  uint16_t port;

  /**
   * flag that indicates if the URI has a port
   * component, if false, port value will be
   * ignored
   */
  bool hasPort;

  /**
   * this flag indicates if the URI is
   * relative
   */
  bool isRelative;

  /**
   * this stores the segments of path
   * in the URI
   */
  std::vector<std::string> path;

  /**
   * this stores the query string component
   * of the URI if present
   */
  std::vector< std::pair< std::string, std::string >> query_string;

  /**
   * this flag indicates whether the URI has
   * a query string component
   */
  bool hasQuery = false;

  /**
   * this stores the fragment part
   * of the query
   */
  std::string fragment;

  /**
   * this flag indicates whether
   * the query has a fragment
   * component
   */
  bool has_fragment = false;

  /**
   * this is a helper method that parses the Scheme
   * part of the URI if present
   *
   * @param[in] uri
   *     uri is the unparsed URI that may contain
   *     the scheme element
   *
   * @param[in] rest
   *     rest stores the substring after the uri has
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
      this->hasProtocol = false;
      rest = uri;
    } else {
      this->hasProtocol = true;
      this->protocol = uri.substr(0, scheme_delimiter);
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
      this->hasPort = false;
      this->host = authority;
    } else {
      this->hasPort = true;
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
      this->isRelative = false;
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
      this->isRelative = true;
      this->isRelative = false;
      pathString = authrorityWithPath;
    }
    return true;
  }

  /**
   * this method parses the path string into
   * a sequence of segments
   *
   * @param[in] pathString
   *     this stores the unparsed path string
   *     of the URI
   *
   * @param[in] rest
   *     this stores the query part and the fragment
   *     path of the URI if present
   */
  bool parsePath(std::string& pathString, std::string& rest) {
    this->path.clear();
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

  bool parseQueryString(std::string& queryString) {
	if (!this->hasQuery) { return true; }
	for(;;) {
		// foo=bar&bar=foo
		size_t queryDelimiter = queryString.find("&");
		if (queryDelimiter == std::string::npos) {
			size_t eqDelimiter = queryString.find("=");
			if (eqDelimiter == std::string::npos) {
				return false;
			} else {
				std::string key = queryString.substr(0, eqDelimiter);
				std::string value = queryString.substr(eqDelimiter + 1);
				this->query_string.emplace_back(std::make_pair(key, value));
			}
			break;
		} else {
			size_t eqDelimiter = queryString.find_first_of("=");
			if (eqDelimiter == std::string::npos) {
				return false;
			} else {
				std::string key = queryString.substr(0, eqDelimiter);
				std::string value = queryString.substr(eqDelimiter + 1, queryDelimiter);
				this->query_string.push_back(std::make_pair(key, value));
			}
			queryString = queryString.substr(queryDelimiter + 1);
		}
	}
	return true;
  }

  std::string formatQueryString() {
	std::stringstream query;
	for (std::pair<std::string, std::string> q : this->query_string) {
		query << q.first << "=" << q.second << "&"; 
	}
	std::string temp = query.str();
	return temp.substr(0, temp.length() - 1);
  }

  std::string formatUriPath() {
    std::stringstream ss;
    for(std::string path : this->path) {
        if (path.length() == 0) {
          ss << "/";
        } else {
            ss << path << "/";
        }
    }
    std::string temp = ss.str();
    return temp.substr(0, temp.length() - 1);
  }
};

Uri::Uri() : impl_(new Impl) {}

bool Uri::parse(const std::string& raw) {
  std::string rest;
  if (!this->impl_->parseScheme(raw, rest)) {
    return false;
  }
  std::string pathStringWithQuery;
  // TODO: if uri has no path but only query, this will fail
  if (!this->impl_->splitAuthorityAndPath(rest, pathStringWithQuery)) {
    return false;
  }
  std::string queryAndFragment;
  std::string pathString;
  size_t pathEndDelimiter = pathStringWithQuery.find("?");
  if (pathEndDelimiter == std::string::npos) {
    this->impl_->hasQuery = false;
    this->impl_->query_string.clear();
    pathString = pathStringWithQuery;
  } else {
    pathString = pathStringWithQuery.substr(0, pathEndDelimiter);
    queryAndFragment = pathStringWithQuery.substr(pathEndDelimiter + 1);
    this->impl_->hasQuery = true;
  }
  if (!this->impl_->parsePath(pathString, queryAndFragment)) {
    return false;
  }

  if (!this->impl_->parseQueryString(queryAndFragment)) {
    return false;
  }
  return true;
}

bool Uri::hasPort() const { return this->impl_->hasPort; }

bool Uri::hasQuery() const { return this->impl_->hasQuery; }


bool Uri::isRelative() const { return this->impl_->isRelative; }


std::string Uri::getProtocol() const {
  if (this->impl_->hasProtocol) {
    return this->impl_->protocol;
  }
  return "";
}

std::string Uri::getHost() const {
    return this->impl_->host;
}

uint16_t Uri::getPort() const { return this->impl_->port; }

std::vector<std::string> Uri::getPath() const { return this->impl_->path; }

std::vector< std::pair< std::string, std::string >> Uri::getQueryString() const {
  this->impl_->query_string;
}

void Uri::setProtocol(std::string scheme) {
	this->impl_->hasProtocol = true;
	this->impl_->protocol = scheme;
}

void Uri::setHost(std::string authority) {
	this->impl_->host = authority;
}

void Uri::setPort(uint16_t port) {
	this->impl_->hasPort = true;
	this->impl_->port = port;
}

void Uri::setPath(std::initializer_list<std::string> path) {
	this->impl_->path = path;
}

void Uri::setQuery(
    std::initializer_list<std::pair<std::string, std::string>> queries) {
	this->impl_->hasQuery = true;
	this->impl_->query_string = queries;
}

std::ostream& operator<<(std::ostream& os, const Uri& uri) {
    if(uri.impl_->hasProtocol && !uri.isRelative()) {
        os << uri.getProtocol() << "://";
    }
    os << uri.getHost();
    if (uri.hasPort()) {
        os << ":" << uri.getPort();
    }
    if (!uri.impl_->path.empty()) {
        os << uri.impl_->formatUriPath();
    } else {
        os << "/";
    }
    if (uri.hasQuery()) {
        os << "?" << uri.impl_->formatQueryString();
    }
    return os;
}

Uri::~Uri() = default;

}  // namespace uri
}  // namespace octo
