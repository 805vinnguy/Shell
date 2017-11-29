#include "mush.h"

int main(void) {

    struct commandline* cmd =
        (struct commandline*)malloc(sizeof(struct commandline));
    struct node* str_list_split_on_pipe;
    struct stage* stages;

    while(TRUE) {
        PARSELINE_SETUP/* getline */
        read_line(cmd);

        check_empty(cmd->bytes);/* checks */
        line_too_long(cmd);

        my_exit(cmd);/* builtins */

        str_list_split_on_pipe = split(cmd->bytes, PIPE_DELIM);
        cmd->pipec = node_list_size(str_list_split_on_pipe);
        too_many_stages(cmd);/* checks */

        stages = parse_line(str_list_split_on_pipe);/* parse */
    }
    
    return 0;
}