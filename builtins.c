#include "builtins.h"

#define EXIT_SUCCESS 0
#define WHITESPACE " \t\r\n\b"
#define BUILTIN_EXIT "exit"
#define BUILTIN_CD "cd"

#define BASH_PWD

void my_cd(struct node* list) {
    char* token;
    char* line =
        (char*)calloc(strlen(list->item)+1, sizeof(char));
    /* if cd not in a pipe */
    if(node_list_size(list) == 1) {
        strcat(line, list->item);
        if( (token = strtok(line, WHITESPACE)) != NULL) {
            if(strcmp(token, BUILTIN_CD) == 0) {
                if( (token = strtok(NULL, WHITESPACE)) != NULL) {
                    safe_cd(token);
                    #ifdef BASH_PWD
                        safe_system("pwd");
                    #endif
                }
            }
        }
    }
    free(line);
}

void safe_system(char* command) {
    if(system(command) == -1) {
        perror("system call");
    }
}

void safe_cd(char* path) {
    if(chdir(path) == -1) {
        perror(BUILTIN_CD);
    }
}

void my_exit(struct commandline* cmd) {
    char* token;
    char* line_rm_spaces = 
        (char*)calloc(strlen(cmd->bytes)+1, sizeof(char));
    strcat(line_rm_spaces, cmd->bytes);
    if( (token = strtok(line_rm_spaces, WHITESPACE)) != NULL) {
        if(strcmp(token, BUILTIN_EXIT) == 0) {
            exit(EXIT_SUCCESS);
        }
    }
    free(line_rm_spaces);
}