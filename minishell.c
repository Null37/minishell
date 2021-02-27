#include "minishell_hr.h"

void command_cd()
{
	write(1, "\033[0;32m", 8);
	int eee = chdir(g_commands->arguments[0]);
	if (eee == -1 && g_commands->arguments[0] != NULL)
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

int	ft_isdigit2(char number)
{
	if (number >= '0' && number <= '9')
	{
		return (1);
	}
	else
		return (0);
}

void command_exit(void)
{
	int lenarg;
	int ex;
	int i;

	i = 0;
	write(1, "exit", 4);
	write(1, "\n", 1);
	lenarg = len_of_args(g_commands->arguments);
	if(g_commands->arguments[0] != NULL)
	{
		while(g_commands->arguments[0][i])
		{
			if(ft_isdigit2(g_commands->arguments[0][i]) == 1)
					i++;
				else
				{
					write(1, "minishell: ", 11);
					write(1, "exit: ", 6);
					write(1, g_commands->arguments[0], strlen(g_commands->arguments[0]));
					write(1, ": ", 2);
					write(1, "numeric argument required", 25);
					write(1, "\n", 1);
					exit(-1);
				}
			}
		}
		if(lenarg == 1 || lenarg == 0)
		{
			if (lenarg == 0)
				ex = 0;
			else
				ex = ft_atoi(g_commands->arguments[0]);
			exit(ex);
		}
		else if (lenarg > 1)
		{
			write(1, "minishell: ", 11);
			write(1, "too many arguments", 18);
			write(1, "\n", 1);	
		}
}

int is_equl(int i, char **envp)
{
	int j = 0;
	while(envp[i][j])
	{
		if(envp[i][j] == '=')
			return 1;
		j++;
	}
	return 0;
}
void command_env(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		if(is_equl(i, envp) == 1)
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

int len_of_args(char **args)
{
	int i = 0;
	if(*args == NULL)
		return 0;
	while(*args != NULL)
	{
		i++;
		args++;
	}
	return i;
}


void ok_write(char **exportp, int i, int j)
{
	int b = 0;
	j = 0;
	write(1, "declare -x ", 11);
	while (exportp[i][j])
	{
		if(exportp[i][j] == '=')
		{
			write(1, "=", 1);
			b = 1;
			write(1, "\"", 1);
			j++;
			break;
		}
		else
			write(1, &exportp[i][j], 1);
		j++;
		
	}
	while (exportp[i][j])
	{
		write(1, &exportp[i][j], 1);
		j++;
	}
	if (b == 1)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

void add_double_quotes(char **exportp)
{
	int lenp;
	int lenarg;
	int k = 0;
	int j = 0;
	int  hh = 0;
	int  i = 0;
	// while(exportp[i] != NULL)
	// {
	// 	j = 0;
	// 	write(1, "declare -x ", 11);
	// 	while(exportp[i][j])
	// 	{
	// 		if(exportp[i][j] == '=')
	// 		{
	// 			write(1, "=", 1);
	// 			write(1, "\"", 1);
	// 		}
	// 		else
	// 		{
	// 			write(1, &exportp[i][j], 1);
	// 		}
	// 		j++;
	// 	}
	// 	write(1, "\"", 1);
	// 	write(1, "\n", 1);
	// 	i++;
	// }


	while (exportp[i] != NULL)
	{
		j = 0;
		while(exportp[i][j])
		{
			if(exportp[i][j] != '=')
			{
				ok_write(exportp, i, j);
				break;
			}
			j++;
		}
		i++;
	}
	
	
}

void check_syntax_export_false(int k, int lenarg)
{
	int i = 0;

	while(g_commands->arguments[k][i])
	{
		if(ft_isalpha(g_commands->arguments[k][0]) == 1 || g_commands->arguments[k][0] == '_')
			i++;
		else if ((ft_isdigit2(g_commands->arguments[k][i]) && i != 0 )|| g_commands->arguments[k][i] == '_')
			i++;
		else
		{
			write(1, "minishell: ", 11);
			write(1, "export: ", 7);
			write(1, "`", 1);
			write(1, g_commands->arguments[k], strlen(g_commands->arguments[k]));
			write(1, "'", 1);
			write(1, ": ", 2);
			write(1, "not a valid identifier", 22);
			write(1, "\n", 1);
			break;
		}
	}
}

void check_syntax_export_true(int k, int lenarg)
{
	int i = 0;

	while(g_commands->arguments[k][i] != '=')
	{
		if(ft_isalpha(g_commands->arguments[k][0]) == 1 || g_commands->arguments[k][0] == '_')
			i++;
		else if ((ft_isdigit2(g_commands->arguments[k][i]) && i != 0 )|| g_commands->arguments[k][i] == '_')
			i++;
		else
		{
			write(1, "minishell: ", 11);
			write(1, "export: ", 7);
			write(1, "`", 1);
			write(1, g_commands->arguments[k], strlen(g_commands->arguments[k]));
			write(1, "'", 1);
			write(1, ": ", 2);
			write(1, "not a valid identifier", 22);
			write(1, "\n", 1);
			break;
		}
	}
}

// void  true_or_false_syntax(int k,char **envp, int true)
// {

// }

void add_in_env(int k, char **envp)
{
	int i;
	
	i = 0;

	while(envp[i] != NULL)
		i++;
	envp[i] = g_commands->arguments[k];
	envp[i + 1] = NULL;
}

void add_in_exp(int k, char **exportp)
{
	int i;
	
	i = 0;

	while(exportp[i] != NULL)
		i++;
	exportp[i] = g_commands->arguments[k];
	exportp[i + 1] = NULL;
}

int  syntax_true(char **envp, int k, int lenarg)
{
	int  i = 0;
	int true;
	while(g_commands->arguments[k][i])
	{
		if(g_commands->arguments[k][i] == '=')
		{
			check_syntax_export_true(k, lenarg);
			add_in_env(k, envp);
			return 1;
		}
		i++;
	}
	return 0;
}

void command_export(char **envp)
{
	int o = nbr_argts(g_commands);
	int i = 0;
	int lenarg;
	int k = 0;
	char **exportp = envp;
	exportp = sort_algo(exportp);
	lenarg = nbr_argts(g_commands) - 1;
	if (o == 1)
		add_double_quotes(exportp);
	else if (o > 1)
	{	
		while (k < lenarg)
		{
			if (syntax_true(envp, k, lenarg) == 0)
			{
				check_syntax_export_false(k, lenarg);
				add_in_exp(k, exportp);
			}
			k++;
		}
	}
}

void check_syntax(int k, int lenarg)
{
	int i = 0;

	while(g_commands->arguments[k][i])
	{
		if(ft_isalpha(g_commands->arguments[k][0]) == 1 || g_commands->arguments[k][0] == '_')
			i++;
		else if ((ft_isdigit2(g_commands->arguments[k][i]) && i != 0 )|| g_commands->arguments[k][i] == '_')
			i++;
		else
		{
			write(1, "minishell: ", 11);
			write(1, "unset: ", 7);
			write(1, "`", 1);
			write(1, g_commands->arguments[k], strlen(g_commands->arguments[k]));
			write(1, "'", 1);
			write(1, ": ", 2);
			write(1, "not a valid identifier", 22);
			write(1, "\n", 1);
			break;
		}
	}

}

char *search_in_env2(char *variable, char **envp)
{
	int lenp;
	int lenarg;
	char *buff;
	char *fsf;
	int k = 0;
	int j = 0;
	int  hh = 0;
	fsf = ft_strdup(" ");
	buff = ft_strdup("");
	lenp = len_of_args(envp);
	lenarg = nbr_argts(g_commands) - 1;

		for (int i = 0; i < lenp; i++)
		{
			if (strncmp(envp[i], variable, strlen(variable)) == 0)
			{
				j = 0;
				while (envp[i][j])
				{
					if(envp[i][j] == '=')
					{
						j += 1;
						while(envp[i][j])
						{
							fsf[0] = envp[i][j];
							buff = ft_strjoin(buff, fsf);
							j++;
						}
						break;
					}
					j++;
				}
			}
		}
	return buff;
}

void command_unset(char **envp)
{
	int lenp;
	int lenarg;
	int k = 0;

	lenp = len_of_args(envp);

	lenarg = nbr_argts(g_commands) - 1;
	while(k < lenarg)
	{
		check_syntax(k ,lenarg);
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
}

void command_variables(char **envp)
{
	
}

void big_putchar()
{
	int i = 0;
	while(g_commands->arguments[i] != NULL)
	{
		ft_putchar(g_commands->arguments[i]);
		write(1, "\n", 1);
		i++;
	}
}

void command_echo()
{
	int o = len_of_args(g_commands->arguments);
	int i = 0;
	if(o == 0)
		write(1, "\n", 1);
	else if (o > 0)
	{
			
		while(g_commands->arguments[i] != NULL)
		{
			ft_putchar(g_commands->arguments[i]);
			if (o > 1)
				write(1, " ", 1);
			i++;
		}
	}
	write(1, "\n", 1);
}

void command_c(int signum)
{
	write(1, "\b\b  ", 4);
	write(1, "\n", 1);
	write(1, "\033[0;33mNull37$\033[0m ", 19);
}

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
	else if(ft_strncmp(g_commands->type, "echo", 6) == 0)
		command_echo();
	else
		return 2;
	return 0;
}

void command_exit_ctr_d(void)
{
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

// int syntax(char ch, int i)
// {
// 	if((ft_isalpha(ch) == 1 && i == 0) || (ch == '_' && i == 0))
// 		return 1;
// 	else if(ft_isalpha(ch) == 1 || ft_isdigit(ch) == 1)
// 		return 1;
// 	return 0;
// }

int check_if_command_is_exist(char *path_file)
{
	int fd;

	fd = open(path_file, O_RDONLY);
	close(fd);
	return fd;
}

int check_this_command(char **envp)
{
	char *path;
	char **command_path;
	int o;
	int fd;
	int i;

	path = search_in_env2("PATH", envp);
	command_path =  ft_split(path, ':');
	o = len_of_args(command_path);
	i = 0;
	
	while(i != o)
	{
		command_path[i] = ft_strjoin(command_path[i], "/");
		command_path[i] = ft_strjoin(command_path[i], g_commands->type);
		fd = check_if_command_is_exist(command_path[i]);
		if (fd == 3)
			return 2;
		else if (fd == -1 &&  i == o - 1)
		{
			write(1, "minishell: ", 11);
			write(1, g_commands->type, ft_strlen(g_commands->type));
			write(1,": ", 2);
			write(1, "command not found\n", 18);
		}
		i++;
	}
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	char *buf;
	char *ptr;
	int errcd;
	char *test;
	buf = NULL;
	char path[200];
	char *line = (char *)malloc(BUFSIZ);
	int readinput;
	while (1)
	{
		signal(SIGINT, command_c);
		write(1, "\033[0;33mNull37$\033[0m ", 19);
		ptr = getcwd(buf, 1024);
		ft_bzero(line, 1024);
		readinput = read(0, line, 1024);
		if(readinput == 0)
			command_exit_ctr_d();
		if (ft_strncmp(line, "\n", 1) != 0)
		{
			if (ft_strchr(line, '\n'))
				*ft_strchr(line, '\n') = '\0';
		}
		g_commands = parssing_shell(envp ,line);
		if(g_commands->multiple == 1)
			continue;
		if (our_command(ptr, envp) == 2 && ft_strncmp(line, "\n", 1) != 0)
		{
			if (check_this_command(envp) == 2)
				write(1, "not work yet\n", 13);
			//fork();
			//test = search_in_env(envp);
			//write(1, test, strlen(test));ƒ
			// int child = fork();
			// if (child == -1) // If fork() fails it does not create a child and returns -1
			// write(1, "Problems\n", 9);
			// if (child == 0) // In the child process
			// {
			// 	if (execve("lsit", g_commands->arguments, envp)) // execve only returns if it encountered an error
			// 	{
			// 		write(1, "Child Problems\n", 15);
			// 		return(-1);
			// 	}
			// }
			 
			//write(1, "\n", 1);
			// 	}
		}
	}
}
