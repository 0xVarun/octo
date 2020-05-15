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

#ifndef __OCTO_CONTROLLER_H_
#define __OCTO_CONTROLLER_H_

#include <octo/http/request.h>
#include <octo/http/response.h>

namespace octo {
namespace service {
class RestController {
public:
    RestController();
    virtual octo::http::Response GET(octo::http::Request* request);
    virtual octo::http::Response POST(octo::http::Request* request);
    virtual octo::http::Response PUT(octo::http::Request* request);
    virtual octo::http::Response PATCH(octo::http::Request* request);
    virtual octo::http::Response DELETE(octo::http::Request* request);
};
} // namespace service
} // namespace octo

#endif // __OCTO_CONTROLLER_H_