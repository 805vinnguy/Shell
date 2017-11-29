#include "builtins.h"

#define EXIT_SUCCESS 0
#define WHITESPACE " \t\r\n\b"

void my_cd(struct node* list) {
    char* token;
    char* line =
        (char*)calloc(strlen(list->item)+1, sizeof(char));
    /* if cd not in a pipe */
    if(node_list_size(list) == 1) {
        strcat(line, list->item);
        if( (token = strtok(line, WHITESPACE)) != NULL) {
            if(strcmp(token, "cd") == 0) {
                if( (token = strtok(NULL, WHITESPACE)) != NULL) {
                    safe_cd(token);
                }
            }
        }
    }
    free(line);
}

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