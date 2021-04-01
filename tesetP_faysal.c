#include "minishell_hr.h"


int main(int ac, char **av, char **envp)
{
    char* ls[] = { "ls", "hh", NULL };
    //char* ls2[] = { "pwd", NULL};

    int a = 5;
        int pid = fork();
        if(pid == 0)
        {
            write(1, "from child\n", 11);
        }
        else
        {
            wait(NULL);
            write(1, "hello from parent ", 18);
        }
    return 1;
}