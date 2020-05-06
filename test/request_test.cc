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
#include <octo/http/request.h>

namespace {
    std::string raw_request = "GET /foo/bar HTTP/1.1\r\n"
        "Host: example.org\r\n"
        "User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; fr; rv:1.9.2.8) Gecko/20100722 Firefox/3.6.8\r\n"
        "Accept: */*\r\n"
        "Accept-Language: fr,fr-fr;q=0.8,en-us;q=0.5,en;q=0.3\r\n"
        "Accept-Encoding: gzip,deflate\r\n"
        "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
        "Keep-Alive: 115\r\n"
        "Connection: keep-alive\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 15\r\n"
        "X-Requested-With: XMLHttpRequest\r\n"
        "Referer: http://example.org/test\r\n"
        "Cookie: foo=bar; lorem=ipsum\r\n"
        "\r\n"
        "foo=bar&bar=foo";

    std::string raw_request_with_qp = "GET /foo/bar?name=octo HTTP/1.1\r\n"
      "Host: example.org\r\n"
      "User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; fr; rv:1.9.2.8) Gecko/20100722 Firefox/3.6.8\r\n"
      "Accept: */*\r\n"
      "Accept-Language: fr,fr-fr;q=0.8,en-us;q=0.5,en;q=0.3\r\n"
      "Accept-Encoding: gzip,deflate\r\n"
      "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
      "Keep-Alive: 115\r\n"
      "Connection: keep-alive\r\n"
      "Content-Type: application/x-www-form-urlencoded\r\n"
      "Content-Length: 15\r\n"
      "X-Requested-With: XMLHttpRequest\r\n"
      "Referer: http://example.org/test\r\n"
      "Cookie: foo=bar; lorem=ipsum\r\n"
      "\r\n"
      "foo=bar&bar=foo";

    std::string raw_invalid_request = "GET /foo/bar?name=octo HTTP/1.1\r\n"
      "Host: example.org\r\n"
      "User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; fr; rv:1.9.2.8) Gecko/20100722 Firefox/3.6.8\r\n"
      "Accept: */*\r\n"
      "Accept-Language: fr,fr-fr;q=0.8,en-us;q=0.5,en;q=0.3\r\n"
      "Accept-Encoding: gzip,deflate\r\n"
      "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
      "Keep-Alive: 115\r\n"
      "Connection: keep-alive\r\n"
      "Content-Type: application/x-www-form-urlencoded\r\n"
      "Content-Length: 15\r\n"
      "X-Requested-With: XMLHttpRequest\r\n"
      "Referer: http://example.org/test\r\n"
      "Cookie: foo=bar; lorem=ipsum\r\n"
      "\r\n"
      "foo=bar&bar=foo\n"
      "WOW THIS SHOULD FAIL";
}

TEST(HTTPRequest, RequestLineTest) {
    octo::http::Request request;
    ASSERT_TRUE(request.parse_http_request(raw_request));
    ASSERT_EQ(request.get_method(), "GET");
    ASSERT_EQ(request.get_path(), "/foo/bar");
    ASSERT_EQ(request.get_http_verion(), "HTTP/1.1");
}

TEST(HTTPRequest, RequestLineTestWithQueryParamUri) {
    octo::http::Request request;
    ASSERT_TRUE(request.parse_http_request(raw_request_with_qp));
    ASSERT_EQ(request.get_method(), "GET");
    ASSERT_EQ(request.get_path(), "/foo/bar?name=octo");
    ASSERT_EQ(request.get_http_verion(), "HTTP/1.1");
}

TEST(HTTPRequest, HeadersTest) {
    octo::http::Request request;
    ASSERT_TRUE(request.parse_http_request(raw_request));
    std::string host_header = request.get_header("Host");
    ASSERT_EQ(host_header, "example.org");
    std::string powered_by_header = request.get_header("X-Powered-By");
    ASSERT_EQ(powered_by_header, "");
}


TEST(HTTPRequest, ContentLengthDoesNotMatch) {
    octo::http::Request request;
    ASSERT_FALSE(request.parse_http_request(raw_invalid_request));
}