#include "builtins.h"

#define EXIT_SUCCESS 0

void safe_cd(char* path) {
    if(chdir(path) == -1) {
        perror("cd");
    }
}

void my_exit(struct commandline* cmd) {
    char* token;
    char* line_rm_spaces = 
        (char*)calloc(strlen(cmd->bytes)+1, sizeof(char));
    strcat(line_rm_spaces, cmd->bytes);
    if( (token = strtok(line_rm_spaces, " \t\r\n\b")) != NULL) {
        if(strcmp(token, "exit") == 0) {
            exit(EXIT_SUCCESS);
        }
    }
    free(line_rm_spaces);
}