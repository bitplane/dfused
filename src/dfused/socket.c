#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#include "../include/dfused.h"
#include "socket.h"


void cleanup() {
    unlink(SOCKET_PATH);
}

int create_socket() {
    int server_fd;
    struct sockaddr_un server_addr;

    // Register the cleanup function to run when the program exits
    atexit(cleanup);

    // Remove the socket if it already exists
    unlink(SOCKET_PATH);

    // Create it
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up the address structure
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void handle_client(int client_fd) {
    char buffer[256];
    int bytes_read;

    // Read data from the client
    bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("read");
        close(client_fd);
        pthread_exit(NULL); // Exit the thread
    }

    buffer[bytes_read] = '\0';
    printf("Received message: %s\n", buffer);

    // Clean up
    close(client_fd);
    pthread_exit(NULL); // Ensure the thread exits after handling the client
}

void* client_handler(void* arg) {
    int client_fd = *(int*)arg;
    free(arg); // Free the dynamically allocated memory

    handle_client(client_fd);

    return NULL;
}

void listen_forever(int server_fd) {
    int* client_fd;
    pthread_t thread_id;

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on %s\n", SOCKET_PATH);

    // Main server loop
    while (1) {
        // Accept a connection
        client_fd = malloc(sizeof(int));
        if (client_fd == NULL) {
            perror("malloc");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        *client_fd = accept(server_fd, NULL, NULL);
        if (*client_fd < 0) {
            perror("accept");
            free(client_fd);
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, client_handler, client_fd) != 0) {
            perror("pthread_create");
            free(client_fd);
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Detach the thread so that resources are released when it finishes
        pthread_detach(thread_id);
    }
}