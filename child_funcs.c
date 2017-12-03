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

int child_exec(struct stage* st, struct pipe_node* p) {
    /* dup appropriate fds to stdin/stdout */
    /* p : NULL or !NULL.
    st->input : file(!original stdin) or !file(original stdin) 
    attempt to fopen st->input: if null (and p=null) then perror 
    if p=null and fopen=null and st->input=original stdin then return
    if p=null and fopen=null and st->input!=original stdin then perror*/
    
    /* close all other fds */
    /* exec command */
}