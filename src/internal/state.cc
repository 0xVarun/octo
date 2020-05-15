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
#include <map>
#include <string>
#include <functional>

#include <octo/http/request.h>
#include <octo/internal/state.h>
#include <octo/service/controller.h>


namespace octo {
namespace internal { 

	State* State::instance;

    struct State::Impl {
        std::map< std::string, octo::service::RestController> routing;
    };

    State::State() : impl_(new Impl) {}

    State* State::getInstance() {
        if (State::instance == nullptr) {
            State::instance = new State();
        }
        return State::instance;
    }

    void State::registerRoute(std::string route, octo::service::RestController controller) {
        if (State::instance->impl_->routing.find(route) == State::instance->impl_->routing.end()) {
            State::instance->impl_->routing.insert(std::make_pair(route, controller));
        } else {
            // log mapping exists
        }
    }

} // namespace internal
} // namespace octo
