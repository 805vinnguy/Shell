#include "io.h"

int get_input(struct stage* st) {
    int fd = safe_dup(STDIN_FILENO);
    if( (strstr(st->input, INPUT_PIPE) != 0) &&
        (strcmp(st->input, INPUT_STDIN) != 0) ) {
        
    }
    return fd;
}

int safe_dup(int oldfd) {
    int newfd;
    if( (newfd = dup(oldfd)) == -1) {
        perror("dup");
        exit(EXIT_CHILD);
    }
    return newfd;
}