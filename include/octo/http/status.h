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

#ifndef __OCTO_STATUS_H_
#define __OCTO_STATUS_H_

#include <map>
#include <string>

#define MAP_ENTRY(x, y) { x, y }

namespace octo {
namespace http {
/**
 * this enum class holds easy to use status
 * response codes for http
 * 
 * @link https://developer.mozilla.org/en-US/docs/Web/HTTP/Status  
 */
enum class StatusCode : unsigned int {
    // 1xx status codes (information responses)
    CONTINUE = 100,
    SWITCHING_PROTOCOL,
    PROCESSING,
    EARLY_HINTS,
    // 2xx status code (successful responses)
    OK = 200,
    CREATED,
    ACCEPTED,
    NON_AUTHORITATIVE_INFORMATION,
    NO_CONTENT,
    RESET_CONTENT,
    PARTIAL_CONTENT,
    // 3xx status codes (redirection message)
    MULTIPLE_CHOICE = 300,
    MOVED_PERMANENTLY,
    FOUND,
    SEE_OTHER,
    NOT_MODIFIED,
    TEMPORARY_REDIRECT = 307,
    PERMANENT_REDIRECT,
    // 4xx status codes (client error)
    BAD_REQUEST = 400,
    UNAUTHORIZED,
    PAYMENT_REQUIRED,
    FORBIDDEN,
    NOT_FOUND,
    METHOD_NOT_ALLOWED,
    NOT_ACCEPTABLE,
    PROXY_AUTH_REQUIRED,
    REQUEST_TIMEOUT,
    CONFLICT,
    GONE,
    LENGTH_REQUIRED,
    
    PRECONDITION_FAILED,
    PAYLOAD_TOO_LARGE,
    URI_TOO_LONG,
    UNSUPPORTED_MEDIA_TYPE,
    RANGE_NOT_SATISFIABLE,
    EXECPTION_FAILED,
    TEAPOT,
    TOO_EARLY = 425,
    UPGRADE_REQURIED,
    PRECONDITION_REQUIRED,
    TOO_MANY_REQUEST,
    REQUEST_HEADER_FIELDS_TOO_LARGE,
    UNAVAILABLE_FOR_LEGAL_REASON,

    // 5xx status codes (server error)
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED,
    BAD_GATEWAY,
    SERVICE_UNAVAILABLE,
    GATEWAT_TIMEOUT,
    HTTP_VERSION_NOT_SUPPORTED,

};

static const std::map< StatusCode, std::string> StatusPharse = {
    MAP_ENTRY(StatusCode::CONTINUE, "Contnue"),
    MAP_ENTRY(StatusCode::SWITCHING_PROTOCOL, "Switching Protocol"),
    MAP_ENTRY(StatusCode::PROCESSING, "Processing"),
    MAP_ENTRY(StatusCode::EARLY_HINTS, "Early Hints"),
    MAP_ENTRY(StatusCode::OK, "OK"),
    MAP_ENTRY(StatusCode::CREATED, "Created"),
    MAP_ENTRY(StatusCode::ACCEPTED, "Accepted"),
    MAP_ENTRY(StatusCode::NON_AUTHORITATIVE_INFORMATION, "Non Authoritative Information"),
    MAP_ENTRY(StatusCode::NO_CONTENT, "No Content"),
    MAP_ENTRY(StatusCode::RESET_CONTENT, "Reset Content"),
    MAP_ENTRY(StatusCode::PARTIAL_CONTENT, "Partial Content"),
    MAP_ENTRY(StatusCode::MULTIPLE_CHOICE, "Multiple Choice"),
    MAP_ENTRY(StatusCode::MOVED_PERMANENTLY, "Moved Permanently"),
    MAP_ENTRY(StatusCode::FOUND, "Found"),
    MAP_ENTRY(StatusCode::SEE_OTHER, "See Other"),
    MAP_ENTRY(StatusCode::NOT_MODIFIED, "Not Modified"),
    MAP_ENTRY(StatusCode::TEMPORARY_REDIRECT, "Temporary Redirect"),
    MAP_ENTRY(StatusCode::PERMANENT_REDIRECT, "Permanent Redirect"),
    MAP_ENTRY(StatusCode::BAD_REQUEST, "Bad Request"),
    MAP_ENTRY(StatusCode::UNAUTHORIZED, "Unauthorized"),
    MAP_ENTRY(StatusCode::PAYMENT_REQUIRED, "Payment Required"),
    MAP_ENTRY(StatusCode::FORBIDDEN, "Forbidden"),
    MAP_ENTRY(StatusCode::NOT_FOUND, "Not Found"),
    MAP_ENTRY(StatusCode::METHOD_NOT_ALLOWED, "Method Not Allowed"),
    MAP_ENTRY(StatusCode::NOT_ACCEPTABLE, "Not Acceptable"),
    MAP_ENTRY(StatusCode::PROXY_AUTH_REQUIRED, "Proxy Authentication Requried"),
    MAP_ENTRY(StatusCode::REQUEST_TIMEOUT, "Request Timeout"),
    MAP_ENTRY(StatusCode::CONFLICT, "Conflict"),
    MAP_ENTRY(StatusCode::GONE, "Gone"),
    MAP_ENTRY(StatusCode::LENGTH_REQUIRED, "Length Required"),
    MAP_ENTRY(StatusCode::PRECONDITION_FAILED, "Precondition Failed"),
    MAP_ENTRY(StatusCode::PAYLOAD_TOO_LARGE, "Payload Too Large"),
    MAP_ENTRY(StatusCode::URI_TOO_LONG, "URI Too Long"),
    MAP_ENTRY(StatusCode::UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type"),
    MAP_ENTRY(StatusCode::RANGE_NOT_SATISFIABLE, "Range Not Satisfiable"),
    MAP_ENTRY(StatusCode::EXECPTION_FAILED, "Exception Failed"),
    MAP_ENTRY(StatusCode::TEAPOT, "I'm a Teapot"),
    MAP_ENTRY(StatusCode::TOO_EARLY, "Too Early"),
    MAP_ENTRY(StatusCode::UPGRADE_REQURIED, "Upgrade Required"),
    MAP_ENTRY(StatusCode::PRECONDITION_REQUIRED, "Precondition Required"),
    MAP_ENTRY(StatusCode::TOO_MANY_REQUEST, "Too Many Requests"),
    MAP_ENTRY(StatusCode::REQUEST_HEADER_FIELDS_TOO_LARGE, "Request Header Field Too Large"),
    MAP_ENTRY(StatusCode::UNAVAILABLE_FOR_LEGAL_REASON, "Unavailable for Legal Reasons"),
    MAP_ENTRY(StatusCode::INTERNAL_SERVER_ERROR, "Internal Server Error"),
    MAP_ENTRY(StatusCode::NOT_IMPLEMENTED, "Not Implemented"),
    MAP_ENTRY(StatusCode::BAD_GATEWAY, "Bad Gateway"),
    MAP_ENTRY(StatusCode::SERVICE_UNAVAILABLE, "Service Unavailable"),
    MAP_ENTRY(StatusCode::GATEWAT_TIMEOUT, "Gatewat Timeout"),
    MAP_ENTRY(StatusCode::HTTP_VERSION_NOT_SUPPORTED, "HTTP Version Not Supported"),
};

} // namespace http
} // namespace octo

#endif // __OCTO_STATUS_H_
