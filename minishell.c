#include "minishell_hr.h"

void command_cd()
{
	write(1, "\033[0;32m", 8);
	int eee = chdir(g_commands->arguments[0]);
	if (eee == -1)
	{
		write(1, "Minishell: ", 11);
		write(1, "cd: ", 4);
		write(1, g_commands->arguments[0], ft_strlen(g_commands->arguments[0]));
		write(1, ": ", 2);
		char *ee = strerror(errno);
		write(1, ee, strlen(ee));
		write(1, "\n", 1);
	}
}

void command_pwd(char *ptr)
{

	char *ech;

	if (ptr != NULL)
	{
		write(1, ptr, strlen(ptr));
		write(1, "\n", 1);
	}
	else
	{
		ech = strerror(errno);
		write(1, ech, ft_strlen(ech));
	}
}

void ft_putchar(char *str)
{
	printf("%s", str);
	write(1, str, strlen(str));
}

void command_exit(void)
{
	write(1, "exit", 4);
	exit(EXIT_SUCCESS);
}

void command_env(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int len_of_args(char **args)
{
	int i = 0;

	while(*args != NULL)
	{
		i++;
		args++;
	}
	return i;
}

void command_export(char **envp)
{
	int o = nbr_argts(g_commands);
	int i = 0;
	if (o == 1 && ft_strncmp(g_commands->type, "export", 7) == 0)
	{
		while (envp[i] != NULL)
		{
			write(1, "declare -x ", 11);
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
			i++;
		}
	}
}

void command_unset(char **envp)
{
	int new_position = 0;
	int lenp;
	int lenarg;
	int k = 0;

	lenp = len_of_args(envp);

	lenarg = nbr_argts(g_commands) - 1;
	while(k < lenarg)
	{
		for (int i = 0; i < lenp; i++)
		{
			if (strncmp(envp[i], g_commands->arguments[k], strlen(g_commands->arguments[k])) == 0)
			{
				int j = i;
				while (j < lenp - 1)
				{
					envp[j] = envp[j + 1];
					j++;
				}
				envp[j]	= NULL;
				lenp = len_of_args(envp);
			}
		}
		k++;
	}
    // if (new_position != i) {
    //     //Move the other elements 
    //     envp[new_position] = envp[i];
    // }
    // new_position++;
	// }

	// lenp = new_position;
}

void command_variables(char **envp)
{

}

/*void command_echo()
{
	int o = len_of_args();

	if(ft_strncmp(args[0], "echo", 4) == 0 && o == 1)
		write(1, "\n", 1);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
	{
		char *str = args[1];
		ft_putchar(str);
		write(1, "\n",1);
	}

}*/

int our_command(char *ptr, char **envp)
{
	if (ft_strncmp(g_commands->type, "cd", 3) == 0)
		command_cd();
	else if (ft_strncmp(g_commands->type, "pwd", 4) == 0)
		command_pwd(ptr);
	else if (ft_strncmp(g_commands->type, "exit", 5) == 0)
		command_exit();
	else if (ft_strncmp(g_commands->type, "env", 4) == 0)
		command_env(envp);
	else if (ft_strncmp(g_commands->type, "export", 7) == 0)
		command_export(envp);
	else if(ft_strncmp(g_commands->type, "unset", 6) == 0)
		command_unset(envp);
	/*else if(ft_strncmp(&args[0][0], "$", 2) == 0)
		command_variables(envp);
	else if(ft_strncmp(args[0], "echo", 6) == 0)
		command_echo(args);*/
	else
		return 2;
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	char *buf;
	char *ptr;
	int errcd;

	buf = NULL;
	char *line = (char *)malloc(1024);
	while (1)
	{
		char path[200];
		write(1, "\033[0;33mNull37$\033[0m ", 19);
		ptr = getcwd(buf, 1024);
		ft_bzero(line, 1024);
		read(0, line, 1024);
		if (ft_strncmp(line, "\n", 1) != 0)
		{
			if (ft_strchr(line, '\n'))
				*ft_strchr(line, '\n') = '\0';
		}
		g_commands = parssing_shell(line);
		if (our_command(ptr, envp) == 2 && ft_strncmp(line, "\n", 1) != 0)
		{
			write(1, "not work yet", 12);
			write(1, "\n", 1);
		}
	}
}
