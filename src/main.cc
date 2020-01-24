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

#include <octo/uri/uri.h>

int main(int argc, char **argv) {
    octo::uri::Uri uri;
    uri.set_scheme("https");
    uri.set_authority("www.google.com");
    uri.set_port(443);
    uri.set_query({std::make_pair("q", "bar"), std::make_pair("utm", "random123")});
    std::cout << uri.to_string() << std::endl;
    // uri.parse("http://example.org/foo/bar?foo=bar&bar=foo");
}
