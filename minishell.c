#include "minishell_hr.h"
 
void command_cd(char **args)
{
	write(1, "\033[0;32m", 8);
	int eee = chdir(args[1]);
	if (eee == -1)
	{
		write(1, "Minishell: ", 11);
		write(1, "cd: ", 4);
		write(1, args[1], strlen(args[1]));
		write(1, ": ", 2);
		char *ee = strerror(errno);
		write(1, ee, strlen(ee));
		write(1, "\n", 1);
	}
}

void command_pwd(char *ptr)
{

	char *ech;

	if(ptr != NULL)
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
    while(envp[i] != NULL)
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

void command_export(char **args, char **envp)
{
	int o = len_of_args(args);
	int  i = 0;
	if(o == 1 && ft_strncmp(args[0], "export", 6) == 0)
	{
		while(envp[i] != NULL)
    	{
       		write(1, "declare -x ", 11);
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
        	i++;
    	}
	}
	
}

void command_unset(char **args, char **envp)
{

}

void command_variables(char **envp)
{

}

void command_echo(char **args)
{
	int o = len_of_args(args);

	if(ft_strncmp(args[0], "echo", 4) == 0 && o == 1)
		write(1, "\n", 1);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
	{
		char *str = args[1];
		ft_putchar(str);
		write(1, "\n",1);
	}

}

int our_command(char **args, char*ptr, char **envp)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		command_cd(args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		command_pwd(ptr);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		command_exit();
	else if (ft_strncmp(args[0], "env", 3) == 0)
		command_env(envp);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		command_export(args, envp);
	else if(ft_strncmp(args[0], "unset", 6) == 0)
		command_unset(args, envp);
	else if(ft_strncmp(&args[0][0], "$", 1) == 0)
		command_variables(envp);
	else if(ft_strncmp(args[0], "echo", 5) == 0)
		command_echo(args);
	else
		return 2;
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	t_commands   *commands;
	char *buf;
	char *ptr;
	int errcd;

	buf = NULL;
	char *r = (char*)malloc(1024);
	while(1)
	{
		//puts("\033[0;33m");
		char path[200];
		write(1, "\033[0;33mNull37$\033[0m ", 19);
		ptr = getcwd(buf, 1024);
		//write(1, ptr, size);
		ft_bzero(r, 1024);
		read(0, r, 1024);
		//write(1, r, strlen(r));
		if(ft_strncmp(r, "\n", 1) != 0)
		{
			if (ft_strchr(r, '\n'))
				*ft_strchr(r, '\n') = '\0';
		}
		commands = parssing_shell(r);
		//char **args = ft_split(r, ' ');
		
		/*if (our_command(args, ptr, envp) == 2 && ft_strncmp(r, "\n", 1) != 0)
		{
			write(1, "not work yet", 12);
			write(1, "\n", 1);
		}*/
	}
	
}
