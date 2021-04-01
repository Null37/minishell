
#include "minishell_hr.h"
void test(char *what, char *path, char **ls2, char **envp)
{
    if(strncmp(what, "pwd", 3)== 0)
        printf("pwd\n");
    else
        execve(path, ls2, envp);
}

int main(int argc, char *argv[], char **envp)
{
    char* ls[] = { "ls", NULL };
    char* ls2[] = { "pwd", NULL};
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if(pid==0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        test("ls", "/bin/ls", ls, envp);
        // test("ls", "/bin/ls", ls, envp);
        // exit(1);
    }
    else
    { 
        pid=fork();

        if(pid==0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            test("pwd", "/bin/ls", ls2, envp);
            // test("pwd", "/bin/ls", ls2, envp);
            // execve("/bin/cat", ls2, envp);
            // exit(1);
        }
        else
        {
            int status;
            close(fd[0]);
            close(fd[1]);
            waitpid(pid, &status, 0);
        }
    }
}
