#include "mush.h"

int main(void) {
    struct commandline* cmd = malloc(sizeof(struct commandline));
    struct node* str_list_split_on_pipe;
    struct stage* stages;

    while(TRUE) {
        read_line(cmd);/* getline */
        my_exit(cmd);/* builtins */
        str_list_split_on_pipe = split(cmd->bytes, PIPE_DELIM);
        my_cd(str_list_split_on_pipe);/* builtins */
        stages = parse_line(str_list_split_on_pipe);
        stage_loop(stages);
    }
    free(cmd);
    return 0;
}

/* place this inside while(TRUE) loop */
void stage_loop(struct stage* stages) {
    struct stage** curr = &stages;
    struct pipe_node* pipe_list;
    struct child_pid_node* child_pid_list = NULL;
    struct child_pid_node* tail = child_pid_list;
    struct child_pid_node* cp;
    pid_t child_pid;

    while(*curr != NULL) {
        /* create pipes */
        pipe_list = make_pipeline(stages);
        /* child_pid = safe_fork();
        cp = make_child_pid_node(child_pid);
        if(child_pid_list == NULL) {
            child_pid_list = cp;
            tail = cp;
        }
        else {
            tail->next = cp;
            tail = cp;
        } */
        /* check if child goes here */
        if(child_pid == 0) {
            /* child_exec */
        }
        /* if parent */
        curr = &((*curr)->next);
    }
}