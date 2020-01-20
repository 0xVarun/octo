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

#include <octo/context.h>
#include <octo/log.h>

int main(int argc, char **argv) {

    octo::Context *ctx = new octo::Context();
    octo::log::Log Log = octo::log::Log::get_instance();
    Log.set_level(octo::log::Log::Level::DEBUG);
    octo::log::Log::INFO("WOE");
    ctx->enable_ssl(true);
    ctx->set_bind_address("0.0.0.0");
    ctx->set_default_headers("Server", "Octo-Frontend");
    ctx->set_port(8080);
    ctx->set_timeout(std::chrono::milliseconds(500));
    ctx->set_worker_limit(5);

}