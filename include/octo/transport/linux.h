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
#ifndef __OCTO_LINUX_H_
#define __OCTO_LINUX_H_

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>

#include <octo/transport/itransport.h>

#include <stout/try.hpp>

namespace octo {
namespace transport {
    class NetworkTransport : public ITransport {
    private:
        NetworkTransport();
    public:
        NetworkTransport(const NetworkTransport&) = delete; // no copy constructor
        NetworkTransport& operator=(const NetworkTransport&) = delete;
        NetworkTransport(NetworkTransport&&) = delete; // no move constructor
        NetworkTransport& operator=(NetworkTransport&&) = delete;
    public:
        ~NetworkTransport();
        static NetworkTransport* init();
        Try<bool> establish(uint16_t port, bool ssl) override;
        void registerReceiveDelegate(ReceiveDelegate receiveDelegate) override;
        Try<bool> transmit(std::vector<uint8_t> payload) override;
        void destory() override;

    private:
        static NetworkTransport* instance;
        struct Impl;
        std::unique_ptr< Impl > impl_;
    };
}
} // namespace octo

#endif // __OCTO_LINUX_H_
