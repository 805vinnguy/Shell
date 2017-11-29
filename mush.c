#include "mush.h"

int main(void) {

    struct commandline* cmd =
        (struct commandline*)malloc(sizeof(struct commandline));
    struct stage* stages;

    while(1) {
        PARSELINE_SETUP/* getline */
        read_line(cmd);

        check_empty(cmd->bytes);/* checks */
        line_too_long(cmd);

        my_exit(cmd);/* builtins */

        stages = parse(cmd);/* parse */
    }
    
    return 0;
}