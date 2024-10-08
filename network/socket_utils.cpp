//
// Created by beloin on 03/01/24.
//

#include "socket_utils.h"
#include <cstdio>

ssize_t Utils::rbytes(int socketfd, unsigned char *buf, size_t n) {
    ssize_t bytes, missing_bytes, total = 0;
    while (total != n) { // Read all bytes into buf
        missing_bytes = ((ssize_t) n) - total;
        size_t index = total;

        // When closed, this returns 0 bytes everytime it recv
        if ((bytes = recv(socketfd, (void *) (buf + index), missing_bytes, 0)) == -1 || bytes == 0) { // or &buf[index]
            if (bytes == -1) {
                perror("could not get bytes");
                return bytes;
            }
            total = bytes;
            break;
        }

        total += bytes;
    }

    return total;
}


ssize_t Utils::sbytes(int socketfd, unsigned char *buf, size_t n) {
    ssize_t bytes, missing_bytes, total = 0;
    while (total != n) {
        missing_bytes = ((ssize_t) n) - total;
        ssize_t index = total;

        if ((bytes = send(socketfd, (void *) (buf + index), missing_bytes, 0)) == -1 || bytes == 0) {
            if (bytes == -1) {
                perror("could not send bytes");
                return bytes;
            }
            total = bytes;
            break;
        }

        total += bytes;
    }

    return total;
}

void *Utils::get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}
