void cleanup();
int create_socket();
void handle_client(int client_fd);
void* client_handler(void* arg);
void listen_forever(int server_fd);