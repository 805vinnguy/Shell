#include "mush.h"

int main(int argc, char* argv[]) {
    struct commandline* cmd = malloc(sizeof(struct commandline));

    if(argc > 1) {
        run_batch_processing(cmd, argv);
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
        if(my_cd(str_list_split_on_pipe) == TRUE) {
            continue;
        }
        stages = parse_line(str_list_split_on_pipe);
        processes = stage_to_process(stages);
        stage_loop(processes);
    }
}

void run_batch_processing(struct commandline* cmd, char* argv[]) {
    struct node* str_list_split_on_pipe;
    struct stage* stages;
    struct process* processes;
    FILE* infile;

    if( (infile = fopen(argv[1], "r")) == NULL ) {
        perror(argv[1]);
        exit(1);
    }
    while(feof(infile) == 0) {
        cmd_init(cmd);
        safe_getline(cmd, infile);
        cmd->bytes[cmd->bytec-1] = '\0';
        my_exit(cmd);
        str_list_split_on_pipe = split(cmd->bytes, PIPE_DELIM);
        if(my_cd(str_list_split_on_pipe) == TRUE) {
            continue;
        }
        stages = parse_line(str_list_split_on_pipe);
        processes = stage_to_process(stages);
        stage_loop(processes);
    }
}

void stage_loop(struct process* processes) {
    struct process** curr = &processes;
    struct child_pid_node* child_pid_list = NULL;
    struct child_pid_node* tail = child_pid_list;
    pid_t child_pid;

    while(*curr != NULL) {
        child_pid = safe_fork();
        tail = add_child_pid(tail, child_pid);
        if(child_pid_list == NULL) {
            child_pid_list = tail;
        }
        if(child_pid == 0) {
            /* dup, cleanup, exec */
            safe_dup2((*curr)->inputfile, STDIN_FILENO);
            safe_dup2((*curr)->outputfile, STDOUT_FILENO);
            cleanup(processes);
            execvp((*curr)->argv[0], (*curr)->argv);
            perror((*curr)->argv[0]);
            exit(EXIT_CHILD);
        }
        curr = &((*curr)->next);
    }
    /* if parent */
    cleanup(processes);
    /* wait */
    wait_all(child_pid_list);
}

void wait_all(struct child_pid_node* list) {
    while(list != NULL) {
        if(waitpid(list->pid, NULL, 0) == -1) {
            perror("waitpid");
        }
        list = list->next;
    }
}

void cleanup(struct process* processes) {
    struct process* to_be_closed = processes;
    while(to_be_closed != NULL) {
        safe_close(to_be_closed->inputfile);
        safe_close(to_be_closed->outputfile);
        to_be_closed = to_be_closed->next;
    }
}

void safe_close(int fd) {
    if((fd == STDIN_FILENO) || (fd == STDOUT_FILENO)) {
        return;
    }
    close(fd);
}

void set_pipes(struct process* processes) {
    struct process** curr = &processes;
    int pipes[2];
    while((*curr != NULL) && ((*curr)->next != NULL)) {
        safe_pipe(pipes);
        (*curr)->outputfile = pipes[WRITE_END];
        ((*curr)->next)->inputfile = pipes[READ_END];
        curr = &((*curr)->next);
    }
}

/* pass ret of this to stage_loop */
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
    set_pipes(processes);
    return processes;
}

int open_input_fd(struct stage** curr, struct stage* stages) {
    if(*curr == stages) {
        if(strcmp((*curr)->input, INPUT_STDIN) != 0) {
            return open((*curr)->input, O_RDONLY);
        }
    }
    return STDIN_FILENO;
}

int open_output_fd(struct stage** curr, struct stage* stages) {
    if((*curr)->next == NULL) {
        if(strcmp((*curr)->output, OUTPUT_STDOUT) != 0) {
            return creat((*curr)->output, S_IRWXU | S_IRWXG | S_IRWXO);
        }
    }
    return STDOUT_FILENO;
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

int process_list_size(struct process* processes) {
    struct process** curr = &processes;
    int len = 0;
    while(*curr != NULL) {
        len++;
        curr = &((*curr)->next);
    }
    return len;
}

struct child_pid_node* add_child_pid(struct child_pid_node* tail, 
                                     pid_t child_pid) {
    struct child_pid_node* cp = make_child_pid_node(child_pid);
    if(cp == NULL) {
        exit(1);
    }
    if(tail != NULL) {
        tail->next = cp;
    }
    return cp;
}