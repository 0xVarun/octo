# Copyright (C) 2020 Varun Tewari
# 
# This file is part of octo.
# 
# octo is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
# 
# octo is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with octo.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(OCTO_VERSION_MAJOR 0)
set(OCTO_VERSION_MINOR 1)
set(OCTO_VERSION_PATCH 0)
set(OCTO_VERSION_STRING 
    ${OCTO_VERSION_MAJOR}.${OCTO_VERSION_MINOR}.${OCTO_VERSION_PATCH})


project(
    Octo
    VERSION ${OCTO_VERSION_STRING}
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(Macros)

find_package(Boost 1.65.1 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
enable_testing()
add_subdirectory(vendor/gtest)

include_directories(include)
add_subdirectory(src)

add_subdirectory(test)
