#include "minishell_hr.h"
#include <string.h>

char **args_g;

void prompt_start()
{
	write(1, "\033[0;33m MINISHELL$ ", 19);
}
void read_line(void)
{
	char *line;

	line = malloc(1024 * sizeof(char));
	ft_bzero(line, 1024);
	if (ft_strchr(line, '\n'))
	*ft_strchr(line, '\n') = '\0';
	int o = read(0, line, 1024);
	
	args_g = ft_split(line, ' ');
	free(line);
}

void command_cd()
{
	int re;
	char *errn;

	write(1, "\033[0;32m", 8);
	re = chdir(args_g[0]);
	if (re == -1)
	{
		write(1, args_g[1], strlen(args_g[1]));
		write(1, ": ", 2);
		errn = strerror(errno);
		write(1, errn, strlen(errn));
		write(1, "\n", 1);
	}
}

void command_pwd()
{

}

void exute_command()
{
	printf("|%s|",  args_g[0]);
	char *cmd = args_g[0];
	if(ft_strncmp(cmd, "cd", 3))
	{
		command_cd();
	}
	// else if(ft_strncmp(args_g[0], "ls", 3))
	// {
	// 	system("ls");
	// }
	// else if (ft_strncmp(args_g[0], "pwd", 4))
	// 	command_pwd();
}

void mini_shell_start(void)
{
	while(1)
	{
		prompt_start();
		read_line();
		exute_command();
	}
}

int main()
{
	mini_shell_start();
}