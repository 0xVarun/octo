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

#ifndef __OCTO_ITRANSPORT_H_
#define __OCTO_ITRANSPORT_H_

#include <string>
#include <vector>
#include <stdint.h>
#include <functional>

#include <stout/try.hpp>

namespace octo {
namespace transport {

    typedef std::function< void(std::vector< uint8_t >) > ReceiveDelegate;

    class ITransport {
    public:
        ITransport() = default;
        ~ITransport() = default;

        virtual Try<bool> establish(uint16_t port, bool ssl) = 0;
        virtual void registerReceiveDelegate(ReceiveDelegate receiveDelegate) = 0;
        virtual Try<bool> transmit(std::vector< uint8_t > payload) = 0;
        virtual void destory() = 0;

    }; // class ITransport

} // namespace transport
} // namespace octo

#endif // __OCTO_ITRANSPORT_H
