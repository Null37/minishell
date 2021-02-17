#include "minishell_hr.h"
#include <string.h>

void prompt_start()
{
    write(1, "\033[0;33m MINISHELL$ ", 19);
}
void read_line(void)
{
    char *line;
    line = malloc(1024 * sizeof(char));
    int o = read(0,line, 1024);
    line[o] = '\0';
    printf("%s", line);
    free(line);
}
void mini_shell_start(void)
{
    while(1)
    {
        prompt_start();
        read_line();

    }
}

int main()
{
    mini_shell_start();
}