#ifndef STAGE_H
#define STAGE_H

/*>>> CONSTANTS <<<*/
#define INVALID_NULL_CMD "invalid null command"
#define PIPE_DELIM "|"
#define SPACE_DELIM " "
#define REDIR_IN "<"
#define REDIR_OUT ">"

/*>>> STRUCTS <<<*/
struct node {
    char* item;
    struct node* next;
};

struct stage {
    char* input;
    char* output;
    int argc;
    char* argv;
    struct node* argv_list;
    struct stage* next;
};

#include "parseline.h"
#include <string.h>

/*>>> FUNCTIONS <<<*/

struct stage* init_stage(void);

int stage_list_size(struct stage* head);

int node_list_size(struct node* head);

struct node* split(char* str, 
                   char* delim);

struct node* make_node(char* item, 
                       struct node* next);
/*------------------------------------------*/
struct stage* build_stage(struct node* list, 
                          char* pipe);

void build_argv(struct node* list, struct stage* n);

struct node* dup_node(struct node* src);

void print_list(struct node* list);

int stage_input(struct node* list,
                 struct stage* n);

int stage_output(struct node* list,
                  struct stage* n);

void pipe_input(struct stage* n, 
                struct node** curr, 
                int i);

void pipe_output(struct stage* n, 
                 struct node** curr, 
                 int i);

#endif