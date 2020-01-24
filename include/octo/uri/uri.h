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
#include <initializer_list>
#include <stdint.h>

namespace octo {
namespace uri {
class Uri {
 public:
  ~Uri();

 public:
  Uri();

  // public methods
  bool parse(const std::string& raw);

  // checks
  bool has_scheme() const;
  bool has_port() const;
  bool has_query() const;

  // getters
  std::string get_scheme() const;
  std::string get_authority() const;
  uint16_t get_port() const;
  std::vector<std::string> get_path() const;
  std::vector< std::pair< std::string, std::string >> get_querys() const;

  // setters
  void set_scheme(std::string scheme);
  void set_authority(std::string authority);
  void set_port(uint16_t port);
  void set_path(std::initializer_list<std::string> path);
  void set_query(
      std::initializer_list<std::pair<std::string, std::string>> queries);

  std::string to_string() const;
 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};  // class Uri
}  // namespace uri

}  // namespace octo

#endif // __OCTO_URI_H_
