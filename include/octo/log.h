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

#ifndef __OCTO_LOG_H_
#define __OCTO_LOG_H_

#include <string>

namespace octo {
namespace log {
class Log {
private:
    Log();
public:
    static Log *instance;
    enum class Level {
        DEBUG = 0x1,
        INFO = 0x2,
        WARN = 0x3,
        CRITICAL = 0x4,
        FATAL = 0x5,
        SECURITY = 0x6
    };
    static Log get_instance();
    static void set_level(Level level);
    static void DEBUG(std::string msg);
    static void INFO(std::string msg);
    static void WARN(std::string msg);
    static void CRITICAL(std::string msg);
    static void FATAL(std::string msg);
    static void SECURITY(std::string msg);
    ~Log();
private:
    Level level;
}; // class Log
} // namespace log
} // namespace octo

#endif // __OCTO_LOG_H_