#include "child_funcs.h"

pid_t safe_fork(void) {
    pid_t child_pid;
    if( (child_pid = fork()) < 0 ) {
        perror("negative child_pid");
        exit(EXIT_CHILD);
    }
    return child_pid;
}

int child_exec(pid_t child_pid, struct stage* st) {
    
    if(child_pid == 0) {

    }
}