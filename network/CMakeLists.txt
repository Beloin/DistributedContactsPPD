add_library(
        network_lib STATIC
        server.cpp server.h
        client.cpp client.h
        socket_utils.cpp socket_utils.h

        know_servers.cpp know_servers.h
)
