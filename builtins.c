#include "builtins.h"

#define EXIT_SUCCESS 0

void my_cd(char* path) {
    if(chdir(path) == -1) {
        perror("cd");
        /*PROMPT*/
    }
}

void my_exit(struct commandline* cmd) {
    if(strcmp(cmd->bytes, "exit") == 0) {
        exit(EXIT_SUCCESS);
    }
}