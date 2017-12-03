#include "io.h"

int get_input(struct stage* st) {
    /* should be the same for both pipe and file.
       no need to dup since fork dups parent's fds */
    if(strcmp(st->input, INPUT_STDIN) != 0) {
        
    }
}

int safe_dup2(int oldfd, int newfd) {
    if( (newfd = dup2(oldfd, newfd)) == -1) {
        perror("dup2");
        exit(EXIT_CHILD);
    }
    return newfd;
}