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

option(BUILD_TRANSPORT_LIBRARY "Build TRANSPORT library" ON)
set(TRANSPORT_BUILD_STYLE STATIC CACHE STRING "Build TRANSPORT as STATIC or SHARED library")

if (${BUILD_TRANSPORT_LIBRARY})
    add_library(
        transport ${TRANSPORT_BUILD_STYLE}
        linux.cc
    )

    target_link_libraries(
        transport
        ${OPENSSL_LIBRARIES}
    )

    add_library(
        octo::transport
        ALIAS
        transport
    )
endif ()

