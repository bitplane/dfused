#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/dfused.h"
#include "socket.h"


int main() {
    int server_fd;

    server_fd = create_socket();
    listen_forever(server_fd);

    close(server_fd);
    return 0;
}
