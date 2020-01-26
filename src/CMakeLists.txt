# Copyright (C) 2020 varun
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


add_subdirectory(uri)
add_subdirectory(http)
add_subdirectory(transport)

add_executable(
    testing
    main.cc
)

target_link_libraries(
    testing
    octo::uri
    octo::http
    octo::transport
)