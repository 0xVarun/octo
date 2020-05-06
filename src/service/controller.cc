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

#include <octo/http/status.h>
#include <octo/http/request.h>
#include <octo/http/response.h>
#include <octo/service/controller.h>

using namespace octo::http;

namespace octo {
namespace service {

    RestController::RestController() {}

    Response RestController::GET(Request* request) {
        Response res;
        res.setStatus(StatusCode::METHOD_NOT_ALLOWED);
        std::string body = "method not allowed at " + request->get_path();
        res.addPayload(body);
        return res;
    }

    Response RestController::POST(Request* request) {
        Response res;
        res.setStatus(StatusCode::METHOD_NOT_ALLOWED);
        std::string body = "method not allowed at " + request->get_path();
        res.addPayload(body);
        return res;
    }

    Response RestController::PUT(Request* request) {
        Response res;
        res.setStatus(StatusCode::METHOD_NOT_ALLOWED);
        std::string body = "method not allowed at " + request->get_path();
        res.addPayload(body);
        return res;
    }

    Response RestController::PATCH(Request* request) {
        Response res;
        res.setStatus(StatusCode::METHOD_NOT_ALLOWED);
        std::string body = "method not allowed at " + request->get_path();
        res.addPayload(body);
        return res;
    }

    Response RestController::DELETE(Request* request) {
        Response res;
        res.setStatus(StatusCode::METHOD_NOT_ALLOWED);
        std::string body = "method not allowed at " + request->get_path();
        res.addPayload(body);
        return res;
    }

} // namespace service
} // namespace octo