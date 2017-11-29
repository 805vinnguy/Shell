#include "builtins.h"

#define EXIT_SUCCESS 0

void safe_cd(char* path) {
    if(chdir(path) == -1) {
        perror("cd");
    }
}

void my_exit(struct commandline* cmd) {
    if(strcmp(cmd->bytes, "exit") == 0) {
        exit(EXIT_SUCCESS);
    }
}