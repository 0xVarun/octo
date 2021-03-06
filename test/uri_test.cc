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

#include <gtest/gtest.h>

#include <octo/uri/uri.h>

TEST(URITest, URIParseFromString) {
  octo::uri::Uri uri;
  ASSERT_TRUE(uri.parse("http://example.org"));
  ASSERT_EQ("http", uri.getProtocol());
  ASSERT_EQ("example.org", uri.getHost());
}

TEST(URITest, URIParseFromStringWithEndingSlash) {
    octo::uri::Uri uri;
    ASSERT_TRUE(uri.parse("http://example.org/foo/bar/"));
    ASSERT_EQ("http", uri.getProtocol());
    ASSERT_EQ("example.org", uri.getHost());
    ASSERT_EQ(
            (std::vector< std::string >{
                "",
                "foo",
                "bar",
                ""
            }),
            uri.getPath()
    );
}

TEST(URITest, URIParseFromStringWithPath) {
  octo::uri::Uri uri;
  ASSERT_TRUE(uri.parse("http://example.org/foo/bar"));
  ASSERT_EQ("http", uri.getProtocol());
  ASSERT_EQ("example.org", uri.getHost());
  ASSERT_EQ((std::vector<std::string>{
                "",
                "foo",
                "bar",
            }),
            uri.getPath());
  ASSERT_FALSE(uri.hasPort());
  ASSERT_FALSE(uri.hasQuery());
}


TEST(URITest, URIParseFromStringWithoutPathWithQueryParameter) {
  octo::uri::Uri uri;
  ASSERT_TRUE(uri.parse("http://example.org/?foo=bar"));
  ASSERT_EQ("http", uri.getProtocol());
  ASSERT_EQ("example.org", uri.getHost());
}

TEST(URITest, URIParseFromStringWithPathWithQueryParameter) {
    octo::uri::Uri uri;
    ASSERT_TRUE(uri.parse("http://example.org/foo/bar?foo=bar"));
    ASSERT_EQ("http", uri.getProtocol());
    ASSERT_EQ("example.org", uri.getHost());
  // ASSERT_EQ("example.org", uri.get_authority());
}


TEST(URITEST,  ParseRelativeURI) {
    octo::uri::Uri uri;
    ASSERT_TRUE(uri.parse("/foo/bar"));
    ASSERT_EQ(
        (std::vector< std::string >{
            "",
            "foo",
            "bar",
        }),
        uri.getPath()
    );
}