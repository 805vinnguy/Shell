#include "parseline.h"

void cmd_init(struct commandline* cmd) {
    cmd->bytec = 0;
    cmd->pipec = 0;
    cmd->buf_size = 0;
    cmd->bytes = NULL;
}

void safe_getline(struct commandline* cmd, FILE* file) {
    size_t i;
    if((cmd->bytec = getline(&(cmd->bytes), &i, file)) == -1) {
        exit(1);
    }
}

struct stage* parse_line(struct node* list) {
    struct node** curr = &list;
    struct node* str_list_split_on_space;
    int i = 0;
    int len = node_list_size(list);
    struct stage* head = NULL;
    struct stage* prev = NULL;
    struct stage* n;

    while(*curr != NULL) {
        if(check_empty((*curr)->item) == TRUE) {
            if(len > 1) {
                fprintf(stderr, "%s\n", "invalid null command");
            }
            break;
        }
        #ifdef PRINT_STAGE_HEADER
            fprintf(stdout, "%s\n", "--------");
            fprintf(stdout, "%s %d: \"%s\"\n", "Stage", i, (*curr)->item);
            fprintf(stdout, "%s\n", "--------");
        #endif
        str_list_split_on_space = split((*curr)->item, SPACE_DELIM);
        n = build_stage(str_list_split_on_space, (*curr)->item);
        if(prev == NULL) {
            head = n;
            prev = n;
        }
        else {
            prev->next = n;
            prev = n;
        }
        first_stage_in(n, i);
        if(pipe_input(n, curr, i) == FALSE) {
            return NULL;
        }
        if(pipe_output(n, curr, i) == FALSE) {
            return NULL;
        }
        #ifdef PRINT_STAGE_BODY
            fprintf(stdout, "input: %s\n", n->input);
            fprintf(stdout, "output: %s\n", n->output);
            fprintf(stdout, "argc: %d\n", n->argc);
            fprintf(stdout, "argv: %s\n", n->argv);
        #endif
        curr = &((*curr)->next);
        i++;
    }
    return head;
}

void print_stages(struct stage* stages) {
    struct stage** curr = &stages;
    int i = 0;
    while(*curr != NULL) {
        #ifdef PRINT_STAGE_HEADER
            fprintf(stdout, "%s\n", "--------");
            fprintf(stdout, "%s %d: \n", "Stage", i);
            fprintf(stdout, "%s\n", "--------");
        #endif
        #ifdef PRINT_STAGE_BODY
            fprintf(stdout, "input: %s\n", (*curr)->input);
            fprintf(stdout, "output: %s\n", (*curr)->output);
            fprintf(stdout, "argc: %d\n", (*curr)->argc);
            fprintf(stdout, "argv: %s\n", (*curr)->argv);
        #endif
        curr = &((*curr)->next);
        i++;
    }
}

int check_empty(char* str) {
    int i;
    for(i = 0; i < strlen(str); i++) {
        if(isspace(str[i]) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void first_stage_in(struct stage* n, int i) {
    if(i == 0) {
        if(n->input == NULL) {
            n->input =
                (char*)calloc(16, sizeof(char));
            memcpy(n->input, "original stdin", 14);
        }
    }
}

void too_many_args(struct stage* n) {
    if(n->argc > CMD_ARG_MAX) {
        fprintf(stderr, "%s\n", "too many arguments");
    }
}

void too_many_stages(struct commandline* cmd) {
    if(cmd->pipec > PIPE_CMD_MAX) {
        fprintf(stderr, "%s\n", "pipeline too deep");
    }
}

void line_too_long(struct commandline* cmd) {
    if(cmd->bytec > CMD_BYTE_MAX) {
        fprintf(stderr, "%s\n", "command too long");
    }
}