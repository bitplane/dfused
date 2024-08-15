#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdint.h>
#include <sys/types.h>

// Enum for message types
typedef enum {
    MSG_TYPE_CONNECT,
    MSG_TYPE_MOUNT,
    MSG_TYPE_UNMOUNT,
    // Add more message types as needed
} MessageType;

// Message header for all messages
typedef struct {
    MessageType type;
} Message;

// Message sent to the server on a connect
typedef struct {
    Message base;
    pid_t pid;
    pid_t tid;  // Note: pthread_t is opaque, so we use pid_t for thread ID
} ConnectMessage;

// Message sent by the server to a client when a new mount point is added
typedef struct {
    Message base;
    uint32_t length;  // Length of the path that follows
    // char path[];    // Path will follow the structure
} MountMessage;

// Message sent by the server to the client when a mount point is removed
typedef struct {
    Message base;
    uint16_t length;  // Length of the path that follows
    // char path[];    // Path will follow the structure
} UnmountMessage;

#endif // MESSAGES_H
