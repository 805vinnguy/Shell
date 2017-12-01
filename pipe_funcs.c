#include "pipe_funcs.h"

void safe_pipe(int pipefd[2]) {
    if(pipe(pipefd) == -1) {
        perror("pipe create failed");
        exit(EXIT_CHILD);
    }
}