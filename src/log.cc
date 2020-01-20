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

#include <string>
#include <iostream>

#include <octo/log.h>

namespace octo {
namespace log {
    
    Log::Log() {
        this->level = Level::DEBUG;
    }

    Log Log::get_instance() {
        if (Log::instance == nullptr) {
            Log::instance = new Log();
        }
        return *Log::instance;
    }

    void Log::set_level(Level level) {
        Log::instance->level = level;
    }

    void Log::DEBUG(std::string msg) {
        std::cout << "[DEBUG] " << msg << std::endl;
    }

    void Log::INFO(std::string msg) {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void Log::WARN(std::string msg) {
        std::cout << "[WARN] " << msg << std::endl;
    }

    void Log::CRITICAL(std::string msg) {
        std::cout << "[CRITICAL] " << msg << std::endl;
    }

    void Log::FATAL(std::string msg) {
        std::cout << "[FATAL] " << msg << std::endl;
    }

    void Log::SECURITY(std::string msg) {
        std::cout << "[SECURITY] " << msg << std::endl;
    }


    Log::~Log() {}

} // namespace log
} // namespace octo