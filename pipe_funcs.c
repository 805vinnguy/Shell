#include "pipe_funcs.h"

void safe_pipe(int pipefd[2]) {
    if(pipe(pipefd) == -1) {
        perror("pipe create failed");
        exit(EXIT_CHILD);
    }
}

struct pipe_node* make_pipe(void) {
    struct pipe_node* p = malloc(sizeof(struct pipe_node));
    safe_pipe(p->pipe_io);
    p->next = NULL;
    return p;
}

struct pipe_node* make_pipeline(struct stage* stages) {
    struct pipe_node* head = NULL;
    struct pipe_node* tail = head;
    struct pipe_node* p;
    struct stage** curr = &stages;
    while(*curr != NULL) {
        p = make_pipe();
        if(head == NULL) {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            tail = p;
        }
        curr = &((*curr)->next);
    }
    return head;
}