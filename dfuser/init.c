#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>


__attribute__((constructor)) void init() {
    printf("Library loaded: Initializing shim...\n");
    fflush(stdout);
}

__attribute__((destructor)) void cleanup() {
    printf("Library unloaded: Cleaning up shim...\n");
    fflush(stdout);
}
