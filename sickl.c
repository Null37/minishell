#include "minishell_hr.h"
typedef struct  s_lst
{
    struct s_lst   *next;
    char            *p2e;
    char            **argv;
}               t_lst;

void add_node(t_lst **head, char *p2e, char **av)
{
    t_lst   **tracer;

    tracer = head;
    while (*tracer)
        tracer = &(*tracer)->next;
    *tracer = malloc(sizeof(**tracer));
    (*tracer)->p2e = strdup(p2e);
    int len;
    for (len = 0; av[len]; len++);
    (*tracer)->argv = malloc(sizeof(char*) * (len + 1));
    for (len = 0; av[len]; len++)
        (*tracer)->argv[len] = strdup(av[len]);
    (*tracer)->argv[len] = NULL;
    (*tracer)->next = NULL;
}

int main(int ac, char **av, char **envp)
{
    t_lst *cmd_list = NULL;
    int i;
    int dfd[2];
    int read_fd;
    int write_fd;

    add_node(&cmd_list, "/bin/ls", (char*[]){"ls", NULL});
    add_node(&cmd_list, "/bin/pwd", (char*[]){"",NULL});
    add_node(&cmd_list, "/usr/bin/cd", (char*[]){"..", NULL});
    add_node(&cmd_list, "/bin/ls", (char*[]){"ls", NULL});
    add_node(&cmd_list, "/bin/cat", (char*[]){"cat", NULL});
    // add_node(&cmd_list, "/usr/bin/head", (char*[]){"head", "-c", "10", NULL});
    // for (t_lst **tr = &cmd_list; *tr; tr = &(*tr)->next)
    // {
    //     printf("cmd: %s\n", (*tr)->p2e);
    //     for (int y = 0; (*tr)->argv[y]; y++)
    //         printf("cmd: %s.arg[%d] = %s\n", (*tr)->p2e, y, (*tr)->argv[y]);
    // }
    i = 0;
    read_fd = dup(0);
    while (cmd_list)
    {
        // fprintf(stderr, "current cmd: %s\n", cmd_list->argv[0]);
        dfd[0] = -1;
        dfd[1] = -1;
        if (cmd_list->next)
        {
            pipe(dfd);
            write_fd = dup( dfd[1]);
            close(dfd[1]);
        }
        else
        {
            write_fd = dup( 1);
        }
        if (fork() == 0)
        {
            //child
            dup2(read_fd, 0);
            dup2(write_fd, 1);
            close(read_fd);
            close(write_fd);
            if (dfd[0] + 1)
                close(dfd[0]);
            if (dfd[1] + 1)
                close(dfd[1]);
            execve(cmd_list->p2e, cmd_list->argv, envp);
            exit(123);
        }
        else
        {
            //parent
            close(read_fd);
            close(write_fd);
            if (cmd_list->next)
            {
                read_fd = dup(dfd[0]);
                close(dfd[0]);
            }
        }
        cmd_list = cmd_list->next;
    }
    while (wait(NULL) > 0);
}