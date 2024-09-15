//
// Created by beloin on 04/01/24.
//
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>


#include "server.h"
#include "socket_utils.h"

#define BACKLOG 10

using Network::Server;

using namespace Network;

int Server::serve(const std::string &port) {
    int server_fd;
    struct addrinfo hints{}, *servinfo, *p;

    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(nullptr, port.data(), &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    }


    for (p = servinfo; p != nullptr; p = p->ai_next) {
        // This get socket information
        if ((server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("serve: socket");
            continue;
        }

        // This enables re-utilization of ports
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(server_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(server_fd);
            perror("serve: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);
    if (p == nullptr) {
        perror("serve: failed to bind");
        exit(1);
    }

    if (listen(server_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

//    std::cout << "serve (" << port << "): waiting for connections..." << std::endl;
    printf("serve (%s): waiting for connections...\n", port.c_str());

    server_on = true;
    serverfd = server_fd;

    while (should_run) {
        struct sockaddr_storage their_addr{};
        socklen_t sin_size = sizeof their_addr;

        // Accept is a cancellation point, so we should be able to kill the serve thread here
        int new_fd = accept(server_fd, (struct sockaddr *) &their_addr, &sin_size);

        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, Utils::get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);
        printf("serve: got connection from %s with fd %d\n", s, new_fd);

        handle_socket(new_fd, s);
    }


    return 0;
}

Server::Server() : should_run(true), server_on(false), isClosed(false) {
}

Network::Server::~Server() {
    if (isClosed) return;

    isClosed = true;
    server_on = false;
    should_run = false;

    close(serverfd);
}

bool Network::Server::IsRunning() const {
    return server_on;
}

void Network::Server::dispose() {
    if (isClosed) return;

    isClosed = true;
    server_on = false;
    should_run = false;

    close(serverfd);
}
