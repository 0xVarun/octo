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


add_library(
    internal STATIC
    state.cc
)

add_library(
    octo::internal
    ALIAS
    internal
)
