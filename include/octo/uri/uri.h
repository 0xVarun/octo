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

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <stdint.h>

namespace octo {
namespace uri {
class Uri {
 public:
  ~Uri();

 public:
  Uri();

  /**
   * this function is responsible
   * for parsing the URI string and
   * storing its components in the class
   * state
   * @param[in] raw
   *     this stores the raw, unparsed
   *     URI string
   * @return bool
   *     an indication whether the URI was
   *     parsed successfully is returned
   */
  bool parse(const std::string& raw);

  // checks
  /**
   * this function returns the hasPort flag
   * from the class state
   * @return bool
   *     an indication whether the URI had a
   *     port component is returned
   */
  bool hasPort() const;

  /**
   * this function returns the hasQuery flag
   * from the class state
   * @return bool
   *     an indication whether the URI had a
   *     query component is returned
   */
  bool hasQuery() const;

  /**
   * this function returns the isRelative flag
   * from the class state
   * @return bool
   *     an indication whether the URI was a
   *     relative URI is returned
   */
  bool isRelative() const;

  // getters
  /**
   * Get the Protocol from the class
   * state
   * @return std::string
   *    stores the return value of the
   *    URI protocol
   * @note if the URI was relative this
   * will return an empty string ("")
   */
  std::string getProtocol() const;

  /**
   * Get the Host from the class
   * state
   * @return std::string
   *     this returns the value of the
   *     URI host
   * @note if the URI was relative this
   * will return an empty string ("")
   */
  std::string getHost() const;

  /**
   * Get the Port from the class
   * state
   * @return uint16_t
   *     this stores the port component
   *     of the URI
   * @note the return value of this function
   * is only valid if @code getPort();@endcode returns true
   */
  uint16_t getPort() const;

  /**
   * Get the Path from the class
   * state
   * @return std::vector<std::string>
   *     this stores individial path
   *     segments of the URI
   * @retval {}
   *     if the URI does not end in
   *     a forward slash
   * @retval {""}
   *     if the URI ends in a forward
   *     slash right after the
   *     authority
   */
  std::vector<std::string> getPath() const;

  /**
   * Get the Query String from
   * the class state
   * @return std::vector< std::pair< std::string, std::string >>
   *     this stores a vector of key-value
   *     pair of the query params in the
   *     URI
   */
  std::vector< std::pair< std::string, std::string >> getQueryString() const;

  // setters
  /**
   * Set the Protocol of
   * the class state
   * @param[in] scheme
   *     this stores the scheme
   *     (protocol) component of
   *     the URI
   */
  void setProtocol(std::string scheme);

  /**
   * Set the Host of
   * the class state
   * @param host
   *     this stores the host
   *     (authority) part of the
   *     URI
   */
  void setHost(std::string host);

  /**
   * Set the Port of
   * the class state
   * @param port
   *     this stores the port
   *     part of the URI
   */
  void setPort(uint16_t port);

  /**
   * Set the Path of the class
   * state
   * @param path
   *     this stores the path
   *     part of the URI
   */
  void setPath(std::initializer_list<std::string> path);

  /**
   * Set the Query of 
   * the class state
   * @param queries
   *     this stores the queries
   *     part of the URI
   */
  void setQuery(
      std::initializer_list<std::pair<std::string, std::string>> queries);

  /**
   * << operator overload to log the
   * URI
   * @param os
   * @return URI
   */
  friend std::ostream& operator<<(std::ostream& os, const Uri& uri);
 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};  // class Uri
}  // namespace uri

}  // namespace octo

#endif // __OCTO_URI_H_
