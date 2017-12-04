#include "stage.h"

struct stage* init_stage(void) {
    struct stage* new = malloc(sizeof(struct stage));
    if(new == NULL) {
        perror("malloc");
        exit(1);
    }
    new->input = NULL;
    new->output = NULL;
    new->argc = 0;
    new->argv = NULL;
    new->argv_list = NULL;
    new->next = NULL;
    return new;
}

int node_list_size(struct node* head) {
    int i = 0;
    struct node** current = &head;
    while(*current != NULL) {
        i++;
        current = &((*current)->next);
    }
    return i;
}

struct node* split(char* str, char* delim) {
    struct node* head = NULL;
    struct node* tail = NULL;
    struct node* new = NULL;
    char* token;

    token = strtok(str, delim);
    while(token != NULL) {
        /*check if token is a space*/
        new = make_node(token, NULL);
        if(tail == NULL) {
            head = new;
            tail = new;
        }
        else {
            tail->next = new;
            tail = new;
        }
        token = strtok(NULL, delim);
    }
    return head;
}

struct node* make_node(char* item, struct node* next) {
    struct node* new =
        (struct node*)malloc(sizeof(struct node));
    new->item = (char*)calloc(strlen(item)+1, sizeof(char));
    memcpy(new->item, item, strlen(item));
    new->next = next;
    return new;
}
/*-------------------------------------------------*/
struct stage* build_stage(struct node* list, char* pipe) {
    struct stage* n = init_stage();
    n->argc = node_list_size(list);
    n->argv = 
        (char*)calloc(strlen(pipe)+3*(n->argc)+1, sizeof(char));

    stage_input(list, n);
    stage_output(list, n);
    build_argv(list, n);
    n->argv_list = list;
    too_many_args(n);
    
    return n;
}

void build_argv(struct node* list, struct stage* n) {
    struct node** curr = &list;
    while(*curr != NULL) {
        strcat(n->argv, "\"");
        strcat(n->argv, (*curr)->item);
        strcat(n->argv, "\"");
        if((*curr)->next != NULL) {
            strcat(n->argv, ",");
        }
        curr = &((*curr)->next);
    }
}

struct node* dup_node(struct node* src) {
    struct node* dest = malloc(sizeof(struct node));
    if(src == NULL) {
        perror("null node cpy");
        exit(1);
    }
    dest->item = (char*)calloc(strlen(src->item)+1, sizeof(char));
    strcat(dest->item, src->item);
    return dest;
}

void print_list(struct node* list) {
    struct node* curr = list;
    while(curr != NULL) {
        fprintf(stdout, "%s\n", curr->item);
        curr = curr->next;
    }
}

int stage_input(struct node* list, struct stage* n) {
    struct node** curr = &list;
    int i = 0;
    while(*curr != NULL) {
        if(strcmp((*curr)->item, "<") == 0) {
            if(n->input != NULL) {
                fprintf(stderr, "%s\n", "bad input redirection");
                exit(1);
            }
            else {
                *curr = (*curr)->next;
                n->argc--;
                if(*curr == NULL) {
                    fprintf(stderr, "%s\n", "bad input redirection");
                    exit(1);
                }
                else {
                    n->input =
                        (char*)calloc(strlen((*curr)->item)+1, sizeof(char));
                    memcpy(n->input, (*curr)->item, strlen((*curr)->item));
                    *curr = (*curr)->next;
                    n->argc--;
                }
            }
        }
        else {
            curr = &((*curr)->next);
        }
    }
    return i;
}

int stage_output(struct node* list, struct stage* n) {
    struct node** curr = &list;
    int i = 0;
    while(*curr != NULL) {
        if(strcmp((*curr)->item, ">") == 0) {
            i = 1;
            if(n->output != NULL) {
                fprintf(stderr, "%s\n", "bad output redirection");
                exit(1);
            }
            else {
                *curr = (*curr)->next;/*remove first*/
                n->argc--;
                if(*curr == NULL) {
                    fprintf(stderr, "%s\n", "bad output redirection");
                    exit(1);
                }
                else {
                    n->output =
                        (char*)calloc(strlen((*curr)->item)+1, sizeof(char));
                    memcpy(n->output, (*curr)->item, strlen((*curr)->item));
                    *curr = (*curr)->next;
                    n->argc--;
                }
            }
        }
        else {
            curr = &((*curr)->next);
        }
    }
    return i;
}

int pipe_input(struct stage* n, struct node** curr, int i) {
    int res = TRUE;
    if(i > 0) {/*not stage 0*/
        if(n->input != NULL) {
            fprintf(stderr, "%s\n", "ambiguous input");
            res = FALSE;
        }
        else {
            n->input =
                (char*)calloc(18, sizeof(char));
            sprintf(n->input, "pipe from stage %d", i-1);
        }
    }
    return res;
}

int pipe_output(struct stage* n, struct node** curr, int i) {
    int res = TRUE;
    if((*curr)->next != NULL) {/*not last stage*/
        if(n->output != NULL) {
            fprintf(stderr, "%s\n", "ambiguous output");
            res = FALSE;
        }
        else {
            n->output =
                (char*)calloc(18, sizeof(char));
            sprintf(n->output, "pipe to stage %d", i+1);
        }
    }
    else {/*is the last stage*/
        if(n->output == NULL) {
            n->output =
                (char*)calloc(16, sizeof(char));
            memcpy(n->output, "original stdout", 15);
        }
    }
    return res;
}