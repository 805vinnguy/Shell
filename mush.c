#include "mush.h"

int main(int argc, char* argv[]) {
    struct commandline* cmd = malloc(sizeof(struct commandline));
    FILE* infile;

    if(argc > 1) {
        /* run_batch_processing() */
    }
    else {
        run_interactive(cmd);
    }
    free(cmd);
    return 0;
}

void run_interactive(struct commandline* cmd) {
    struct node* str_list_split_on_pipe;
    struct stage* stages;
    struct process* processes;

    while(TRUE) {
        cmd_init(cmd);
        fprintf(stdout, "%s", PROMPT);
        fflush(stdout);
        safe_getline(cmd, stdin);
        cmd->bytes[cmd->bytec-1] = '\0';
        my_exit(cmd);
        str_list_split_on_pipe = split(cmd->bytes, PIPE_DELIM);
        my_cd(str_list_split_on_pipe);
        stages = parse_line(str_list_split_on_pipe);
        stage_loop(stages);
    }
}

/* void run_batch_processing(struct commandline* cmd, char* argv[]) {
    struct str_list_split_on_pipe;
    struct stage* stages;

    if( (file = fopen(argv[1], "r")) == NULL ) {
        perror(argv[1]);
        exit(1);
    }

} */

/* place this inside while(TRUE) loop */
void stage_loop(struct stage* stages) {
    struct stage** curr = &stages;
    int fd_input;
    int fd_output;
    struct pipe_node* pipe_list;/* pipe_list = pipe_list->next */
    struct child_pid_node* child_pid_list = NULL;
    struct child_pid_node* tail = child_pid_list;
    struct child_pid_node* cp;
    pid_t child_pid;

    while(*curr != NULL) {
        /* open input/output fds */
        if(*curr == stages) {
            fd_input = open((*curr)->input, O_RDONLY);
        }
        if((*curr)->next == NULL) {
            fd_output = creat((*curr)->output, S_IRWXU | S_IRWXG | S_IRWXO);
        }
        /* create pipes */
        pipe_list = make_pipeline(stages);
        /* child_pid = safe_fork();
        cp = make_child_pid_node(child_pid);
        if(child_pid_list == NULL) {
            child_pid_list = cp;
            tail = cp;
        }
        else {
            tail->next = cp;
            tail = cp;
        } */
        /* check if child goes here */
        if(child_pid == 0) {
            /* child_exec */
            /* pass it stages, curr_pipe */
            /* dup, cleanup, exec */
        }
        /* if parent */
        curr = &((*curr)->next);
    }
}

struct process* stage_to_process(struct stage* stages) {
    struct stage** curr = &stages;
    struct process* processes = NULL;
    struct process* end = NULL;
    struct process* p;
    while(*curr != NULL) {
        p = malloc(sizeof(struct process));
        p->inputfile = open_input_fd(curr, stages);
        p->outputfile = open_output_fd(curr, stages);
        p->argv = nodelist_to_stringlist(*curr);
        if(processes == NULL) {
            processes = p;
            end = p;
        }
        else {
            end->next = p;
            end = p;
        }
        curr = &((*curr)->next);
    }
    return processes;
}

int open_input_fd(struct stage** curr, struct stage* stages) {
    if(*curr == stages) {
        if(strcmp((*curr)->input, INPUT_STDIN) != 0) {
            return open((*curr)->input, O_RDONLY);
        }
        else {
            return STDIN_FILENO;
        }
    }
}

int open_output_fd(struct stage** curr, struct stage* stages) {
    if((*curr)->next != NULL) {
        if(strcmp((*curr)->output, OUTPUT_STDOUT) != 0) {
            return creat((*curr)->output, S_IRWXU | S_IRWXG | S_IRWXO);
        }
        else {
            return STDOUT_FILENO;
        }
    }
}

char** nodelist_to_stringlist(struct stage* s) {
    struct node** curr = &(s->argv_list);
    char** stringlist = (char**)malloc((s->argc+1)*sizeof(char*));
    int i = 0;
    while(*curr != NULL) {
        stringlist[i] = (*curr)->item;
        curr = &((*curr)->next);
        i++;
    }
    return stringlist;
}