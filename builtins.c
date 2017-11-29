#include "builtins.h"

#define EXIT_SUCCESS 0

void safe_cd(char* path) {
    if(chdir(path) == -1) {
        perror("cd");
    }
}

void my_exit(struct commandline* cmd) {
    if(strstr(cmd->bytes, "exit") != NULL) {
        exit(EXIT_SUCCESS);
    }
}