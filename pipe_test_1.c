#include "minishell_hr.h"

int main()
{
    int fd[2];
    int pid;
    pipe(fd);
    pid = fork();
    
    if(pid == 0)
    {
        close(fd[0]);
        int n;
        printf("git me => ");
        write(1, "===>", 4);
        write(1, &n, sizeof(int));
        close(fd[1]);
    }
    else
    {
        int st;
        waitpid(pid, &st, 0);
        close(fd[1]);
        int h;
        read(fd[0], &h, sizeof(int));
        close(fd[0]);
        write(1, &h, sizeof(int));
    }

    return (0);
}