#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include "../include/dfused.h"
#include "connection.h"

// Thread-specific data for the daemon connection
__thread int daemon_socket_fd = -1;

// Function to connect to the daemon socket
static int connect_to_daemon() {
    int sockfd;
    struct sockaddr_un addr;

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, DAEMON_SOCKET, sizeof(addr.sun_path) - 1);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

// Each thread that does IO currently has its own connection to the daemon.
int get_daemon_connection() {
    if (daemon_socket_fd == -1) {
        daemon_socket_fd = connect_to_daemon();
        if (daemon_socket_fd == -1) {
            perror("Failed to connect to daemon\n");
            exit(EXIT_FAILURE);
        }
    }
    return daemon_socket_fd;
}
