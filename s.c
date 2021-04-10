#include "minishell_hr.h"

int main(int ac, char **av, char **ep) {
    char **argv = (char*[]){"cat", NULL};
    int in = open("ls", O_RDONLY);
    int out = open("99", O_WRONLY | O_APPEND);
    int save_in = dup(0);
    int save_out = dup(1);
    dup2(in, 0);
    dup2(out, 1);
    close(in);
    close(out);
    if (fork() == 0) {
        //child
        execve("/bin/cat", argv, ep);
        fprintf(stderr, "err\n");
    }
    else {
        //parent
        wait(NULL);
        // close(in);
        // close(out);
        dup2(save_in, 0);
        dup2(save_out, 1);
        close(save_in);
        close(save_out);
    }
    printf("hello:\n");
    char str[50];
    scanf("%s", str);
    printf("str = %s\n", str);
}