#include "mush.h"

int main(void) {
    struct commandline* cmd = malloc(sizeof(struct commandline));
    struct node* str_list_split_on_pipe;
    struct stage* stages;
    struct child_pid_node* child_pid_list;

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
    pid_t child_pid;

    while(*curr != NULL) {
        /* child_pid = safe_fork(); */
        /* check if child goes here */
        curr = &((*curr)->next);
    }
}