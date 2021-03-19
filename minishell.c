#include "minishell_hr.h"

void command_cd(t_commands *tmp)
{
	write(1, "\033[0;32m", 8);
	int eee = chdir(tmp->arguments[0]);
	if (eee == -1 && tmp->arguments[0] != NULL)
	{
		write(2, "Minishell: ", 11);
		write(2, "cd: ", 4);
		write(2, tmp->arguments[0], ft_strlen(tmp->arguments[0]));
		write(2, ": ", 2);
		char *ee = strerror(errno);
		write(2, ee, strlen(ee));
		write(2, "\n", 1);
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

void command_exit(t_commands *tmp)
{
	int lenarg;
	int ex;
	int i;
	i = 0;
	write(1, "exit", 4);
	write(1, "\n", 1);
	lenarg = len_of_args(tmp->arguments);
	if(tmp->arguments[0] != NULL)
	{
		while(tmp->arguments[0][i])
		{
			if(ft_isdigit2(tmp->arguments[0][i]) == 1)
					i++;
				else
				{
					write(2, "minishell: ", 11);
					write(2, "exit: ", 6);
					write(2, tmp->arguments[0], strlen(tmp->arguments[0]));
					write(2, ": ", 2);
					write(2, "numeric argument required", 25);
					write(2, "\n", 1);
					free(tmp->arguments[0]);
					tmp->arguments[0] = NULL;
					exit(-1);
				}
			}
		}
		if(lenarg == 1 || lenarg == 0)
		{
			if (lenarg == 0)
				ex = 0;
			else
				ex = ft_atoi(tmp->arguments[0]);
			free(tmp->arguments[0]);
			tmp->arguments[0] = NULL;
			//kill(tmp->pid, SIGKILL);
			exit(ex);
		}
		else if (lenarg > 1)
		{
			write(2, "minishell: ", 11);
			write(2, "too many arguments", 18);
			write(2, "\n", 1);	
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

int check_syntax_export_false(t_commands *tmp ,int k, int lenarg)
{
	int i = 0;

	while(tmp->arguments[k][i])
	{
		if(ft_isalpha(tmp->arguments[k][0]) == 1 || tmp->arguments[k][0] == '_')
			i++;
		else if ((ft_isdigit2(tmp->arguments[k][i]) && i != 0 )|| tmp->arguments[k][i] == '_')
			i++;
		else
		{
			write(1, "minishell: ", 11);
			write(1, "export: ", 7);
			write(1, "`", 1);
			write(1, tmp->arguments[k], strlen(tmp->arguments[k]));
			write(1, "'", 1);
			write(1, ": ", 2);
			write(1, "not a valid identifier", 22);
			write(1, "\n", 1);
			return 1;
		}
	}
	return 0;
}

int check_syntax_export_true(t_commands *tmp,int k, int lenarg)
{
	int i = 0;
	while(tmp->arguments[k][i] != '=')
	{
		if(ft_isalpha(tmp->arguments[k][i]) == 1 || tmp->arguments[k][i] == '_')
			i++;
		else if ((ft_isdigit2(tmp->arguments[k][i]) == 1 && i != 0 )|| tmp->arguments[k][i] == '_')
			i++;
		else
		{
			write(1, "minishell: ", 11);
			write(1, "export: ", 7);
			write(1, "`", 1);
			write(1, tmp->arguments[k], strlen(tmp->arguments[k]));
			write(1, "'", 1);
			write(1, ": ", 2);
			write(1, "not a valid identifier", 22);
			write(1, "\n", 1);
			return 1;
		}
	}
	return 0;
}

// void  true_or_false_syntax(int k,char **envp, int true)
// {

// }

void add_in_env(t_commands *tmp, int k, char **envp)
{
	int i;
	int j;
	int b =0;
	int c = 0;
	int lenp;
	char *nameenv;

	lenp =0;
	j = 0;
	i = 0;
	while(tmp->arguments[k][b] != '=')
			b++;
	char *varibale = malloc(sizeof(char) * b + 1);
	while(c != b)
	{
		varibale[c] = tmp->arguments[k][c];
		c++;
	}
	varibale[c] = '\0';
	char *ef = search_in_env2(varibale, envp);
	while(envp[i] != NULL)
		i++;
	if(ft_strncmp(ef, "\0", 1) == 0)
	{
		envp[i] = tmp->arguments[k];
		envp[i + 1] = NULL;
	}
	else
	{
		b += 1;
		char *te = (tmp->arguments[k] + b);
		int t;
		int tee = 0;;

		t = ft_strlen(te);
		lenp = len_of_args(envp);
		for (int i = 0; i < lenp; i++)
		{
			nameenv = get_env_name(envp[i]);
			if (my_strcmp(nameenv, varibale) == 0)
			{
				// j = 0;
				
				// while (envp[i][j])
				// {
				// 	if(envp[i][j] == '=')
				// 	{
				// 		j += 1;
				// 		envp[i] = (char*)malloc(sizeof(char) * t);
				// 		while(tee != t)
				// 		{
				// 			envp[i][j] = tmp->arguments[k][b];
				// 			j++;
				// 			b++;
				// 			tee++;
				// 		}
						
				// 	}
				// 	j++;
				// }
				varibale = ft_strjoin(varibale, "=");
				envp[i] = ft_strjoin(varibale, te);
						// envp[i] = ft_strjoin(envp[i], (g_commands->arguments[k] + b));
						// envp[i] = ft_strjoin(envp[i],(g_commands->arguments[k] + b));
				return;
				/// if n=
				// envp[i] = ft_strjoin(envp[i], "=");
				// j++;
				// while(tee != t)
				// {
				// 	envp[i][j] = g_commands->arguments[k][b];
				// 	j++;
				// 	b++;
				// 	tee++;
				// }
				// envp[i][j] ='\0';
				// envp[i] = ft_strjoin(envp[i], (g_commands->arguments[k] + b));
				// return;
			}
		}
	}
}

void add_in_exp(t_commands *tmp, int k, char **exportp)
{
	int i;
	int j;
	int b =0;
	int c = 0;
	int lenp;

	lenp =0;
	j = 0;
	i = 0;

	//char *varibale = malloc(sizeof(char) * 500);

	char *varibale = tmp->arguments[k];
	char *ef = search_in_env2(varibale, exportp);
	
	while(exportp[i] != NULL)
		i++;
	if(ft_strncmp(ef, "\0", 1) == 0)
	{
		exportp[i] = tmp->arguments[k];
		exportp[i + 1] = NULL;
	}
	else
	{
		b += 1;
		char *te = (tmp->arguments[k] + b);
		int t;
		int tee = 0;;

		t = ft_strlen(te);
		lenp = len_of_args(exportp);
		for (int i = 0; i < lenp; i++)
		{
			int g = 0;
			while(varibale[g])
			{
				if(varibale[g] == '=')
					break;
				g++;
			}
			if(varibale[g] == '\0')
				continue;
			if (my_strcmp(exportp[i], varibale) == 0)
			{
				j = 0;
				while (exportp[i][j])
				{
					if(exportp[i][j] == '=')
					{
						j += 1;
						while(tee != t)
						{
							exportp[i][j] = tmp->arguments[k][b];
							j++;
							b++;
							tee++;
						}
						exportp[i][j] ='\0';
						break;
					}
					j++;
				}
			}
		}
	}
}

int  syntax_true(t_commands *tmp, char **envp, int k, int lenarg)
{
	int  i = 0;
	int true;
	while(tmp->arguments[k][i])
	{
		if(tmp->arguments[k][i] == '=')
		{
			if (check_syntax_export_true(tmp, k, lenarg) == 0)
				add_in_env(tmp, k, envp);
			return 1;
		}
		i++;
	}
	return 0;
}

void command_export(t_commands *tmp, char **envp)
{
	int o = nbr_argts(tmp);
	int i = 0;
	int lenarg;
	int k = 0;
	char **exportp = envp;
	exportp = sort_algo(exportp);
	lenarg = nbr_argts(tmp) - 1;
	if (o == 1)
		add_double_quotes(exportp);
	else if (o > 1)
	{	
		while (k < lenarg)
		{
			if (syntax_true(tmp, envp, k, lenarg) == 0)
			{
				if (check_syntax_export_false(tmp ,k, lenarg) == 0)
					add_in_exp(tmp,k, exportp);
			}
			k++;
		}
	}
}

void check_syntax(t_commands *tmp,int k, int lenarg)
{
	int i = 0;

	while(tmp->arguments[k][i])
	{
		if(ft_isalpha(tmp->arguments[k][0]) == 1 || tmp->arguments[k][0] == '_')
			i++;
		else if ((ft_isdigit2(tmp->arguments[k][i]) && i != 0 )|| tmp->arguments[k][i] == '_')
			i++;
		else
		{
			write(1, "minishell: ", 11);
			write(1, "unset: ", 7);
			write(1, "`", 1);
			write(1, tmp->arguments[k], strlen(tmp->arguments[k]));
			write(1, "'", 1);
			write(1, ": ", 2);
			write(1, "not a valid identifier", 22);
			write(1, "\n", 1);
			break;
		}
	}

}
int my_strcmp(char *s1, char *s2)
{
  int i;
  i = -1;
  int j = -1;
  if (!s1 || !s2)
    return (1);
  while (1)
  {
    if (s1[++i] != s2[++j])
      return (1);
    if (s1[i] == '\0' || s2[j] == '\0')
      break ;
  }
  return (0);
}

char *get_env_name(char *envp)
{
	int b = 0;
	int c = 0;

	while(envp[b])
	{
		if(envp[b] == '=')
			break;
		b++;
	}
	char *varibale = malloc(sizeof(char) * b + 1);
	while(c != b)
	{
		varibale[c] = envp[c];
		c++;
	}
	varibale[c] = '\0';
	return (varibale);
}

char *search_in_env2(char *variable, char **envp)
{
	int lenp;
	int lenarg;
	char *nameenv;
	char *buff;
	char *fsf;
	int k = 0;
	int j = 0;
	int  hh = 0;
	fsf = ft_strdup(" ");
	buff = ft_strdup("");
	lenp = len_of_args(envp);
	// lenarg = nbr_argts(g_commands) - 1;

		for (int i = 0; i < lenp; i++)
		{
			nameenv = get_env_name(envp[i]);
			if (my_strcmp(nameenv, variable) == 0)
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
						return buff;
					}
					j++;
				}
				buff = "k";
				return buff;
			}
		}
	return buff;
}

void command_unset(t_commands *tmp ,char **envp)
{
	int lenp;
	int lenarg;
	int k = 0;

	lenp = len_of_args(envp);

	lenarg = nbr_argts(tmp) - 1;
	while(k < lenarg)
	{
		check_syntax(tmp, k ,lenarg);
		for (int i = 0; i < lenp; i++)
		{
			if (strncmp(envp[i], tmp->arguments[k], strlen(tmp->arguments[k])) == 0)
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

void command_echo(t_commands *tmp)
{
	int o = len_of_args(tmp->arguments);
	int i = 0;
	if(o == 0)
		write(1, "\n", 1);
	else if (o > 0)
	{
			
		while(tmp->arguments[i] != NULL)
		{
			ft_putchar(tmp->arguments[i]);
			if (o > 1)
				write(1, " ", 1);
			i++;
		}
	}
	write(1, "\n", 1);
}

void command_c(int signum)
{
	if(fuck != 0)
		write(1, "\b\b  ", 4);
	write(1, "\n", 1);
	write(1, "\033[0;33mNull37$\033[0m ", 19);
	fuck = 1;
}

void command_in_the_sys(t_commands *tmp, char **envp)
{
	// int pid;
	//char* argv[] = {"ls","-la",NULL};
	int stat_loc;
	char *error;
	pid = 0;
	pid = fork();
	//g_commands->pid = pid;
        if (pid == 0) 
		{
            /* Never returns if the call is successful */
            if(execve(tmp->path, tmp->all, envp) < 0)
			{
				error = strerror(errno);
				write(2, "minishell: ", 11);
				write(2, tmp->type, ft_strlen(tmp->type));
				write(2, ": ", 2);
				write(2, error, ft_strlen(error));
				write(2, "\n", 1);
				exit(-1);
			}
        } 
		else 
		{
            waitpid(pid, &stat_loc, WUNTRACED);
			if(stat_loc == 256)
				stat_loc = 1;
			printf("%d", stat_loc);
        }
}
int our_command(t_commands *tmp, char *ptr, char **envp)
{
	// t_commands *tmp;
	// tmp = g_commands;
	// while (1)
	// {
		//check_this_command(tmp,envp);
		if(tmp->type == NULL && tmp->next)
		{
			write(2, "minishell: syntax error near unexpected token `;'", 49);
			write(2, "\n", 1);
			return -1;
		}
		else if (tmp->type == NULL && !tmp->next)
			return 0;
		if (ft_strncmp(tmp->type, "cd", 3) == 0)
			command_cd(tmp);
		else if (ft_strncmp(tmp->type, "pwd", 4) == 0)
			command_pwd(ptr);
		else if (ft_strncmp(tmp->type, "exit", 5) == 0)
			command_exit(tmp);
		else if (ft_strncmp(tmp->type, "env", 4) == 0)
			command_env(envp);
		else if (ft_strncmp(tmp->type, "export", 7) == 0)
			command_export(tmp, envp);
		else if(ft_strncmp(tmp->type, "unset", 6) == 0)
			command_unset(tmp, envp);
		else if(ft_strncmp(tmp->type, "echo", 6) == 0)
			command_echo(tmp);
		else
			command_in_the_sys(tmp, envp);
	// 	if (!tmp->next)
	// 		break ;
	// 	tmp = tmp->next;
	// }
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

int check_this_command(t_commands *tmp,char **envp)
{
	char *path;
	char **command_path;
	int o;
	int fd;
	int i;
	if (my_strcmp("exit", tmp->type) == 0 || my_strcmp("export", tmp->type) == 0
	|| my_strcmp("unset", tmp->type) == 0)
		return 2;
	path = search_in_env2("PATH", envp);
	command_path =  ft_split(path, ':');
	o = len_of_args(command_path);
	i = 0;
	while(i != o)
	{
		if(ft_strncmp(tmp->type, "/", 1) != 0)
		{
			command_path[i] = ft_strjoin(command_path[i], "/");
			command_path[i] = ft_strjoin(command_path[i], tmp->type);
			fd = check_if_command_is_exist(command_path[i]);
		}
		else if(ft_strncmp(tmp->type, "/", 1) == 0)
		{
			fd = check_if_command_is_exist(tmp->type);
			DIR* dir = opendir(tmp->type);
			if(dir == NULL)
			{
				tmp->path = tmp->type;
				return 2;
			}
			else if (dir)
			{
				write(2, "minishell: ", 11);
				write(2, tmp->type, ft_strlen(tmp->type));
				write(2, ": ", 2);
				write(2, "is a directory\n", 15);
				closedir(dir);
				return 0;
			}
			else if(ENOENT == errno)
			{
				char *error = strerror(errno);
				write(2, error, ft_strlen(error));
				write(2, "\n", 1);
			}
			// if(fd < 0)
			// {
			// 	char *error = strerror(errno);
			// 	write(2, error, ft_strlen(error));
			// 	return 0;
			// }
		}
		if (fd == 3)
		{
			tmp->path = command_path[i];
			return 2;
		}
		else if (fd == -1 &&  i == o - 1)
		{
			write(1, "minishell: ", 11);
			write(1, tmp->type, ft_strlen(tmp->type));
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
	fuck = 0;
	while (1)
	{
		signal(SIGINT, command_c);
		// signal(SIGQUIT, command_c);
		if (fuck == 0)
		{
			write(1, "\033[0;33mNull37$\033[0m ", 19);
			fuck = 1;
		}
		ptr = getcwd(buf, 1024);
		ft_bzero(line, 1024);
		readinput = read(0, line, 1024);
		fuck = 0;
		if(readinput == 0)
			command_exit_ctr_d();
		if (ft_strncmp(line, "\n", 1) != 0)
		{
			if (ft_strchr(line, '\n'))
				*ft_strchr(line, '\n') = '\0';
		}
		g_commands = parssing_shell(ptr, envp ,line);
		if(g_commands->multiple == 1)
			continue;
		// if (our_command(ptr, envp) == 2 && ft_strncmp(line, "\n", 1) != 0)
		// {
		// 	if (check_this_command(envp) == 2)
		// 		write(1, "not work yet\n", 13);
		// 	//fork();
		// 	//test = search_in_env(envp);
		// 	//write(1, test, strlen(test));ƒ
		// 	// int child = fork();
		// 	// if (child == -1) // If fork() fails it does not create a child and returns -1
		// 	// write(1, "Problems\n", 9);
		// 	// if (child == 0) // In the child process
		// 	// {
		// 	// 	if (execve("lsit", g_commands->arguments, envp)) // execve only returns if it encountered an error
		// 	// 	{
		// 	// 		write(1, "Child Problems\n", 15);
		// 	// 		return(-1);
		// 	// 	}
		// 	// }
			 
		// 	//write(1, "\n", 1);
		// 	// 	}
		// }
	}
}
//export "Hello World=test"
//export A;
// export ttat@tet=test
//(ft_isalpha(g_commands->arguments[k][0]) != 1 || g_commands->arguments[k][0] != '_' || (ft_isdigit2(g_commands->arguments[k][i]) && i != 0)  || g_commands->arguments[k][i] != '_')