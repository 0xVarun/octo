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

#include <stout/try.hpp>

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

    Try<bool> NetworkTransport::establish(uint16_t port, bool ssl = false) {
        if (this->impl_->recv == nullptr) {
            exit(-1);
        }
        int status;
        this->impl_->port = port;
        this->impl_->ssl = ssl;

        if (ssl) {
            SSL_load_error_strings();
            SSL_library_init();
            OpenSSL_add_all_algorithms();
        }

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
            this->impl_->sslContext = SSL_CTX_new(TLS_server_method());
            SSL_CTX_set_options(this->impl_->sslContext, SSL_OP_SINGLE_DH_USE);
            
            int use_cert = SSL_CTX_use_certificate_file(this->impl_->sslContext, "/home/varun/sandbox/octo/key/cert.pem" , SSL_FILETYPE_PEM);
            int use_prv = SSL_CTX_use_PrivateKey_file(this->impl_->sslContext, "/home/varun/sandbox/octo/key/key.pem", SSL_FILETYPE_PEM);

            this->impl_->sslI = SSL_new(this->impl_->sslContext);
            SSL_set_fd(this->impl_->sslI, incoming);
            int ssl_err = SSL_accept(this->impl_->sslI);
            const char *resp = response.serialize().c_str();
            SSL_write(this->impl_->sslI, "resp", strlen("resp"));
            break;
            delete[] buff;
        }

    }

    void NetworkTransport::registerReceiveDelegate(ReceiveDelegate receiveDelegate) {
        this->impl_->recv = receiveDelegate;
    }

    Try<bool> NetworkTransport::transmit(std::vector<uint8_t> payload) {
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
        if (this->impl_->ssl) {
            SSL_shutdown(this->impl_->sslI);
            SSL_free(this->impl_->sslI);
        } 
    }

    NetworkTransport::~NetworkTransport() {
        if (this->impl_->ssl) {
            ERR_free_strings();
            EVP_cleanup();
        }
        this->destory();
    }

} // namespace transport
} // namespace octo