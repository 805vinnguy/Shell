#include "child_funcs.h"

pid_t safe_fork(void) {
    pid_t child_pid;
    if( (child_pid = fork()) >= 0 ) {
        return child_pid;
    }
    perror("negative child_pid");
    return -1;
}

int child_exec(pid_t child_pid, struct stage* st) {

    if(child_pid == 0) {
        
    }
}