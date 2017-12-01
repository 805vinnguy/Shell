#ifndef PARSELINE_H
#define PARSELINE_H

/*>>> CONSTANTS <<<*/
#define TRUE 1
#define FALSE 0
#define UNLIMITED 40960
#define CMD_BYTE_MAX 1024
#define PIPE_CMD_MAX 10
#define CMD_ARG_MAX 10
#define PROMPT "8-P "

#include "stage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

/*>>> DEFINITIONS <<<*/
/* #define PRINT_STAGE_HEADER
#define PRINT_STAGE_BODY */

/*>>> STRUCTS <<<*/
struct commandline {
    ssize_t bytec;
    size_t buf_size;
    char* bytes;
    int pipec;
};

/*>>> MACROS <<<*/
#define CHECK_VALID_FORK { \
    if( (child_pid = fork()) < 0) { \
        perror("negative child_pid"); \
        exit(1); \
    } \
}/*not used in parseline*/

#define PARSELINE_SETUP { \
    fprintf(stdout, "%s", PROMPT); \
    fflush(stdout); \
    cmd->bytec = 0; \
    cmd->pipec = 0; \
    cmd->buf_size = 0; \
    cmd->bytes = NULL; \
}

/*>>> FUNCTIONS <<<*/
void read_line(struct commandline* cmd);

void safe_getline(struct commandline* cmd);

struct stage* parse_line(struct node* list);

void print_stages(struct stage* stages);

int check_empty(char* str);

void first_stage_in(struct stage* n, 
                    int i);
                
void too_many_args(struct stage* n);

void too_many_stages(struct commandline* cmd);

void line_too_long(struct commandline* cmd);

#endif