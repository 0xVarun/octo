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

#ifndef __OCTO_INTERNAL_STATE_H_
#define __OCTO_INTERNAL_STATE_H_

#include <memory>
#include <octo/service/controller.h>

namespace octo {
namespace internal {
class State {
private:
    ~State() = delete;
    State(const State&) = delete;
    State(State&&) = delete;
    State& operator=(const State&) = delete;
    State& operator=(State&&) = delete;
private:
    static State* instance;
    State();
public:
    /**
     * Get the Instance of the State object
     * @return State* instance of state
     */
    static State* getInstance();
    
    /**
     * Register a controller class for a route
     * @param route String route 
     * @param controller RestController class object
     */
    static void registerRoute(std::string route, octo::service::RestController controller);
private:
    struct Impl;
    std::unique_ptr< struct Impl > impl_;
};
} // namespace internal
} // namespace octo

#endif // __OCTO_INTERNAL_STATE_H_