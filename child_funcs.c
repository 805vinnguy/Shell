#include "child_funcs.h"

pid_t safe_fork(void) {
    pid_t child_pid;
    if( (child_pid = fork()) < 0 ) {
        perror("negative child_pid");
        exit(EXIT_CHILD);
    }
    return child_pid;
}

struct child_pid_node* make_child_pid_node(pid_t child_pid) {
    struct child_pid_node* cp = malloc(sizeof(struct child_pid_node));
    cp->pid = child_pid;
    cp->next = NULL;
    return cp;
}