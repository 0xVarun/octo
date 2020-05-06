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

#include <iostream>
#include <cstring>
#include <string>

#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#include <octo/http/response.h>
#include <octo/http/request.h>
#include <octo/transport/linux.h>


namespace {
    void socketErrorReport(int status, int LINE = 0) {
        if (status < 0)
            std::cerr << "[-] error ("  << LINE << ") "<< strerror(status) << std::endl;
    }
}

namespace octo {
namespace transport {

    NetworkTransport* NetworkTransport::instance = nullptr;

    struct NetworkTransport::Impl {
        uint16_t port = 0;
        bool ssl = false;
        int serverFd;
        SSL_CTX *sslContext;
        SSL *sslI;
        ReceiveDelegate recv = nullptr;
    };

    NetworkTransport::NetworkTransport() : impl_(new Impl) {}

    NetworkTransport* NetworkTransport::init() {
        if (instance == nullptr) {
            instance = new NetworkTransport();
        }
        return instance;
    }

    bool NetworkTransport::establish(uint16_t port, bool ssl = false) {
        if (this->impl_->recv == nullptr) {
            exit(-1);
        }
        int status;
        this->impl_->port = port;
        this->impl_->ssl = ssl;

        struct sockaddr_in server;
        int enableSocketOptions;
        this->impl_->serverFd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        status = setsockopt(this->impl_->serverFd, SOL_SOCKET, SO_REUSEADDR, &enableSocketOptions, sizeof(int));
        socketErrorReport(status);

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htons(INADDR_ANY);
        server.sin_port = htons(port);

        status = bind(this->impl_->serverFd, (struct sockaddr *)&server, sizeof(server));
        socketErrorReport(status);

        listen(this->impl_->serverFd, 50);

        socklen_t size = sizeof(server);

        for (;;) {
            int incoming = accept(this->impl_->serverFd, (struct sockaddr *)&server, &size);
            socketErrorReport(incoming, __LINE__);
            break;
        }
        return true;
    }

    void NetworkTransport::registerReceiveDelegate(ReceiveDelegate receiveDelegate) {
        this->impl_->recv = receiveDelegate;
    }

    bool NetworkTransport::transmit(std::vector<uint8_t> payload) {
        size_t transmitted = send(this->impl_->serverFd, payload.data(), payload.size(), 0);
        if (transmitted < 0) {
            return false;
        }
        return true;
    }

    void NetworkTransport::destory() {
        if (fcntl(this->impl_->serverFd, F_GETFD)) {
            close(this->impl_->serverFd);
            this->impl_->serverFd = -1;
        }
    }

    NetworkTransport::~NetworkTransport() {
        this->destory();
    }

} // namespace transport
} // namespace octo