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

// int	check_rdr(char *s, int i)
// {
// 	if (s[i] == '>' && s[i + 1] == '>')
// 		return (2);
	
// 	return (0);
// }

// int check_syntax_rederction(char **av)
// {
// 	int i = -1;
// 	int j = 0;
// 	int h = 0;
// 	int right = 0;
// 	int ch = 0;
// 	while (av[1][++i])
// 	{
// 		if (av[1][i] == '>' || av[1][i] == '<')
// 			check_rdr(av[1], i);
// 	}
// 	return 0;
// }

