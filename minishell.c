/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:14:40 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/14 14:14:43 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

char **edit_evp_new_oldpwd(char *ptr, char **envp_c)
{
	char *nameenv;
	int lenp = len_of_args(envp_c);
	int j;
	int o = 0;
	for (int i = 0; i < lenp; i++)
		{
			nameenv = get_env_name(envp_c[i]);
			if (my_strcmp(nameenv, "OLDPWD") == 0)
			{
					free(envp_c[i]);
					int len = ft_strlen(ptr);
					j = ft_strlen(nameenv);
					envp_c[i] =  (char*)malloc(len  + j + 1 + 2);
					int t = 0;
					while(1)
					{
						int h = 0;
						while(j > 0)
						{
							envp_c[i][h] = nameenv[o];
							o++;
							h++;
							j--;
						}
						j = ft_strlen(nameenv);
						envp_c[i][j] = '=';
						while(len > 0)
						{
							j++;
							envp_c[i][j] = ptr[t];
							t++;
							len--;
						}
						break;
					}
					envp_c[i][j +1] = '\0';
				break;
			}
		}
	return (envp_c);
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

void command_exit(t_commands *tmp, int pipe)
{
	int lenarg;
	int ex;
	int i;
	i = 0;
	if(pipe == 0)
	{
		write(2, "exit", 4);
		write(2, "\n", 1);
	}
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
			exit(ex);
		}
		else if (lenarg > 1)
		{
			write(2, "minishell: ", 11);
			write(2, "too many arguments", 18);
			g_all->staus_code = 1;
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


int len_of_args(char **args)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		i++;
	}
	return (i);
}


void ok_write(char **my_env, int i, int j)
{
    int b = 0;
    j = 0;
    write(1, "declare -x ", 11);
    while (my_env[i][j])
    {
        if(my_env[i][j] == '=')
        {
            write(1, "=", 1);
            b = 1;
            write(1, "\"", 1);
            j++;
            break;
        }
        else
            write(1, &my_env[i][j], 1);
        j++;
    }
    while (my_env[i][j])
    {
        if (my_env[i][j] == '\\' || my_env[i][j] == '$')
            write(1, "\\", 1);
        write(1, &my_env[i][j], 1);
        j++;
    }
    if (b == 1)
        write(1, "\"", 1);
    write(1, "\n", 1);
}


void	mini_redrection(t_commands *tmp, char *ptr,t_env *evp)
{
	t_filerdr *t;
	t = tmp->filerdr;
	int saved_stdout;
	int saved_input;
	char *stre;
	redir_fd = -100;
	redir_fd_in = -100;
	int fd = -200;
	int fd_in = -100;
	if(check_two_red(tmp) == 0)
	{
		t_filerdr *lastnamef = last_name_func(tmp);
		if(!lastnamef)
			return ;
		if(check_if_command_is_exist(tmp->filerdr->name, 0) == 3)
			return ;
		if(lastnamef->type == 0)
		{
			fd_in = open(lastnamef->name, O_RDONLY);
			saved_input = dup(0);
			close(0);
			dup2(fd_in, 0);
			if(check_this_command(tmp,evp) == 2)
				our_command(tmp, ptr, evp);
			dup2(saved_input, 0);
			close(saved_input);
			close(fd_in);
		}
		else if(lastnamef->type == 1)
		{
			//output
			fd = open(lastnamef->name,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
			saved_stdout = dup(1);
			close(1);
			dup2(fd, 1);
			if(check_this_command(tmp,evp) == 2)
				our_command(tmp, ptr, evp);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
			close(fd);
		}
		else if(lastnamef->type == 2)
		{
			//output
			fd = open(lastnamef->name, O_CREAT|O_WRONLY|O_APPEND, 0644);
			saved_stdout = dup(1);
			close(1);
			dup2(fd, 1);
			if(check_this_command(tmp,evp) == 2)
				our_command(tmp, ptr, evp);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
			close(fd);
		}
	}

	else if(check_two_red(tmp) == 1)
	{
		yesdup = 1;
		// fprintf(stderr, "here\n");
		// saved_input = dup(0);
		// saved_stdout = dup(1);
		redir_fd = output_ret(tmp);
		if(redir_fd == -100)
			return;
		redir_fd_in = input_ret(tmp);
		if(redir_fd_in == -100)
			return ;
		if(check_this_command(tmp,evp) == 2)
			our_command(tmp, ptr, evp);
		yesdup = 0;
		// dup2(saved_input, 0);
		// dup2(saved_stdout, STDOUT_FILENO);
		// close(saved_stdout);
		// close(saved_input);
	}
}

void add_double_quotes(char **my_env)
{
	int lenp;
	int lenarg;
	int k = 0;
	int j = 0;
	int  hh = 0;
	int  i = 0;

	while (my_env[i] != NULL)
	{
		j = 0;
		while(my_env[i][j])
		{
			if(my_env[i][j] != '=')
			{
				ok_write(my_env, i, j);
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
		if(ft_isalpha(tmp->arguments[k][i]) == 1 || tmp->arguments[k][i] == '_')
			i++;
		else if ((ft_isdigit2(tmp->arguments[k][i]) == 1 && i != 0 ) || tmp->arguments[k][i] == '_')
			i++;
		else
		{
			write(2, "minishell: ", 11);
			write(2, "export: ", 7);
			write(2, "`", 1);
			write(2, tmp->arguments[k], strlen(tmp->arguments[k]));
			write(2, "'", 1);
			write(2, ": ", 2);
			write(2, "not a valid identifier", 22);
			write(2, "\n", 1);
			g_all->staus_code = 1;
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
			write(2, "minishell: ", 11);
			write(2, "export: ", 7);
			write(2, "`", 1);
			write(2, tmp->arguments[k], strlen(tmp->arguments[k]));
			write(2, "'", 1);
			write(2, ": ", 2);
			write(2, "not a valid identifier", 22);
			write(2, "\n", 1);
			g_all->staus_code = 1;
			return 1;
		}
	}
	return 0;
}

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
				varibale = ft_strjoin(varibale, "=");
				envp[i] = ft_strjoin(varibale, te);
				return;
			}
		}
	}
}

void add_in_exp(t_commands *tmp, int k, char **my_env)
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
	char *ef = search_in_env2(varibale, my_env);
	lenp = len_of_args(my_env);
	while(my_env[i] != NULL)
		i++;
	if(ft_strncmp(ef, "\0", 1) == 0)
	{
		my_env[i] = tmp->arguments[k];
	}
	else
	{
		b += 1;
		char *te = (tmp->arguments[k] + b);
		int t;
		int tee = 0;;

		t = ft_strlen(te);
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
			if (my_strcmp(my_env[i], varibale) == 0)
			{
				j = 0;
				while (my_env[i][j])
				{
					if(my_env[i][j] == '=')
					{
						j += 1;
						while(tee != t)
						{
							my_env[i][j] = tmp->arguments[k][b];
							j++;
							b++;
							tee++;
						}
						my_env[i][j] ='\0';
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
	int i;

	i = 0;
	while(tmp->arguments[k][i])
	{
		if(tmp->arguments[k][0] == '=')
		{
			write(2, "minishell: ", 11);
			write(2, "export: ", 7);
			write(2, "`", 1);
			write(2, tmp->arguments[k], strlen(tmp->arguments[k]));
			write(2, "'", 1);
			write(2, ": ", 2);
			write(2, "not a valid identifier", 22);
			write(2, "\n", 1);
			g_all->staus_code = 1;
			return 1;
		}
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


int count_arg_2(t_commands *tmp)
{
	int i = -1;
	int cpt = 0;

	while(tmp->arguments[++i] != NULL)
			cpt++;
	return (cpt);
}

void command_export(t_commands *tmp, t_env *evp)
{
	int o = count_arg_2(tmp);
	int i = 0;
	int lenarg;
	char *s;
	int k = 0;
	int z;
	evp->my_env = sort_algo(evp->my_env);
	lenarg = o;
	if (o == 0)
		add_double_quotes(evp->my_env);
	else if (o > 0)
	{
		char **tprr;
		int lenp = len_of_args(evp->my_env);
		tprr = malloc(sizeof(char*) * (lenp + o + 1));
		tprr[lenp + o] = NULL;
		z = -1;
		while(tprr[++z] != NULL)
			tprr[z] = NULL;
		z = -1;
		while(evp->my_env[++z] != NULL)
		{
			tprr[z] = evp->my_env[z];
		}
		free(evp->my_env);
		evp->my_env = tprr;
		while (k < lenarg)
		{
			if (syntax_true(tmp, evp->my_env, k, lenarg) == 0)
			{
				if (check_syntax_export_false(tmp ,k, lenarg) == 0)
					add_in_exp(tmp,k, evp->my_env);
			}
			k++;
		}
	}
	g_all->staus_code = 0;
}


void check_syntax(t_commands *tmp,int k, int lenarg, char e_u)
{
	int i = 0;

	while(tmp->arguments[k][i])
	{
		if(ft_isalpha(tmp->arguments[k][i]) == 1 || tmp->arguments[k][i] == '_')
			i++;
		else if ((ft_isdigit2(tmp->arguments[k][i]) && i != 0 )|| tmp->arguments[k][i] == '_')
			i++;
		else
		{
			write(2, "minishell: ", 11);
			if(e_u == 'u')
				write(1, "unset: ", 7);
			else if(e_u == 'e')
				write(1, "export: ", 8);
			write(2, "`", 1);
			write(2, tmp->arguments[k], strlen(tmp->arguments[k]));
			write(2, "'", 1);
			write(2, ": ", 2);
			write(2, "not a valid identifier", 22);
			write(2, "\n", 1);
			g_all->staus_code = 1;
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

void command_unset(t_commands *tmp ,t_env *evp)
{
	int lenp;
	int lenarg;
	int k = 0;

	lenp = len_of_args(evp->my_env);

	lenarg = count_arg_2(tmp);
	while(k < lenarg)
	{
		check_syntax(tmp, k ,lenarg, 'u');
		for (int i = 0; i < lenp; i++)
		{
			if (strncmp(evp->my_env[i], tmp->arguments[k], strlen(tmp->arguments[k])) == 0)
			{
				int j = i;
				while (j < lenp - 1)
				{
					evp->my_env[j] = evp->my_env[j + 1];
					j++;
				}
				evp->my_env[j]	= NULL;
				lenp = len_of_args(evp->my_env);
			}
		}
		k++;
	}
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

void command_c(int signum)
{
	g_all->staus_code = 1;
	write(1, "\n", 1);
	write(1, "\033[0;33mNull37$\033[0m ", 19);
	if(g_all->ret)
	{
		free(g_all->ret);
		g_all->ret = NULL;
	}
	g_all->ctrl_c = 1;
}

void	error_execve(t_commands *tmp)
{
	char	*error;

	error = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, tmp->type, ft_strlen(tmp->type));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	g_all->staus_code = 127;
}

int our_command(t_commands *tmp, char *ptr, t_env *evp)
{
	char *test;

	test = search_in_env2("PWD", evp->my_env);
	if (ft_strncmp(test, "", 1) != 0)
		g_all->old_pwd = search_in_env2("PWD", evp->my_env);
	if (tmp->type == NULL && !tmp->next)
		return 0;
	if (ft_strncmp(tmp->type, "cd", 3) == 0)
		command_cd(ptr,tmp, evp);
	else if (ft_strncmp(tmp->type, "pwd", 4) == 0)
		command_pwd(ptr, evp);
	else if (ft_strncmp(tmp->type, "exit", 5) == 0)
		command_exit(tmp, 0);
	else if (ft_strncmp(tmp->type, "env", 4) == 0)
		command_env(evp->my_env);
	else if (ft_strncmp(tmp->type, "export", 7) == 0)
		command_export(tmp, evp);
	else if(ft_strncmp(tmp->type, "unset", 6) == 0)
		command_unset(tmp, evp);
	else if(ft_strncmp(tmp->type, "echo", 6) == 0)
		command_echo(tmp);
	else
		command_in_the_sys(tmp,evp->my_env);
	return 0;
}

void command_exit_ctr_d(void)
{
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

int check_permissions(char *path_file, struct stat stats, int exute)
{
	if ((stats.st_mode & R_OK) && (stats.st_mode & W_OK) && exute == 0)
	   return 1;
	else if((stats.st_mode & X_OK) && exute == 1)
	{
		return 2;
	}
	else if((!(stats.st_mode & R_OK) && !(stats.st_mode & X_OK)) || (!(stats.st_mode & X_OK) && exute == 1))
	{
		write(2, "minishell: ", 11);
		write(2, path_file, ft_strlen(path_file));
		write(2, ": ", 2);
		write(2,"Permission denied\n", 18);
		return 1;
	}
	return 0;
}

int check_file_or_dit(char *path_file)
{
	DIR *dir;
    struct dirent *dp;
	dir = opendir(path_file);
	if(dir != NULL)
	{
		write(2, "minishell: ", 11);
		write(2, path_file, ft_strlen(path_file));
		write(2, ": ", 2);
		write(2, "is a directory\n", 15);
		return 3;
	}
	return 0;
}
int check_if_command_is_exist(char *path_file, int exute)
{
	int fs;
	struct stat buf;

	fs = stat(path_file, &buf);
	if (fs == 0)
	{
		if(check_file_or_dit(path_file) == 3)
			return 3;
		if (check_permissions(path_file, buf, exute) == 1)
			return 3;
	}
	return fs;
}

void print_error_check_commd(t_commands *tmp)
{
	char *eir = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, tmp->type, ft_strlen(tmp->type));
	write(2, ": ", 2);
	write(2, eir, strlen(eir));
	write(2, "\n", 1);
}



void se_execute_command(t_commands *tmp, char *ptr, t_env *evp)
{
	if (ft_strncmp(tmp->type, "cd", 3) == 0)
		command_cd(ptr, tmp, evp);
	else if (ft_strncmp(tmp->type, "pwd", 4) == 0)
		command_pwd(ptr,evp);
	else if (ft_strncmp(tmp->type, "exit", 5) == 0)
		command_exit(tmp, 1);
	else if (ft_strncmp(tmp->type, "env", 4) == 0)
		command_env(evp->my_env);
	else if (ft_strncmp(tmp->type, "export", 7) == 0)
		command_export(tmp, evp);
	else if(ft_strncmp(tmp->type, "unset", 6) == 0)
		command_unset(tmp, evp);
	else if(ft_strncmp(tmp->type, "echo", 6) == 0)
		command_echo(tmp);
	else
	{
		if (execve(tmp->path, tmp->all, evp->my_env) < 0)
			error_execve(tmp);
	}
}

t_filerdr *last_name_func(t_commands *tmp)
{
	t_filerdr *head;
	t_filerdr *last;
	int fd = -70;
	head = tmp->filerdr;
	char *err;
	while (1)
	{
		if (head->type == 0)
		{
			fd = open(head->name, O_RDONLY);
			if(fd < 0)
			{
				err = strerror(errno);
				write(2, "minishell: ", 11);
				write(2, head->name, ft_strlen(head->name));
				write(2, ": ", 2);
				ft_putstr_fd(err, 2);
				write(2, "\n", 1);
				return NULL;
			}
			last = head;
			close(fd);
		}
		else if (head->type == 1)
		{
			fd = open(head->name,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
			last = head;
			close(fd);
		}
		else if (head->type == 2)
		{
			fd = open(head->name, O_CREAT, 0644);
			last = head;
			close(fd);
		}
		
		if (!head->next)
			break ;
		head = head->next;
	}
	return(last);
}

int output_ret(t_commands *tmp)
{
	t_filerdr *head;
	int fd = -17;
	head = tmp->filerdr;
	char *err;
	int fd_check = -50;
	while (1)
	{
		if (head->type == 0)
		{
			fd_check = open(head->name, O_RDONLY);
			if(fd_check < 0)
			{
				err = strerror(errno);
				write(2, "minishell: ", 11);
				write(2, head->name, ft_strlen(head->name));
				write(2, ": ", 2);
				ft_putstr_fd(err, 2);
				write(2, "\n", 1);
				close(fd_check);
				return (-100);
			}
			close(fd_check);
		}
		if (head->type == 1)
		{
			close(fd);
			fd = open(head->name,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (head->type == 2)
		{
			close(fd);
			fd = open(head->name, O_CREAT|O_WRONLY|O_APPEND, 0644);
		}
		if (!head->next)
			break ;
		head = head->next;
	}
	return(fd);
}

int input_ret(t_commands *tmp)
{
	t_filerdr *head;
	int fd = -12;
	head = tmp->filerdr;
	char *err;
	while (1)
	{
		if (head->type == 0)
		{
			close(fd);
			fd = open(head->name, O_RDONLY);
			if(fd < 0)
			{
				err = strerror(errno);
				write(2, "minishell: ", 11);
				write(2, head->name, ft_strlen(head->name));
				write(2, ": ", 2);
				ft_putstr_fd(err, 2);
				write(2, "\n", 1);
				return (-100);
			}
		}
		if (!head->next)
			break ;
		head = head->next;
	}
	return(fd);
}

int check_two_red(t_commands *tmp)
{

	t_filerdr *head;
	int cpt = 0;
	int cpt2 = 0;
	head = tmp->filerdr;
	char *err;
	while (1)
	{		
		if (head->type == 0)
		{
			cpt = 1;
		}
		else if (head->type == 1)
		{
			cpt2 = 1;
		}
		else if (head->type == 2)
		{
			cpt2 = 1;
		}
		if (!head->next)
			break ;
		head = head->next;
	}
	if(cpt == 1 && cpt2 == 1)
		return (1);
	return(0);
}

void  pipe_commmand_c(t_commands *tmp, char *ptr, t_env *evp)
{
	int i;
	int fd[2];
	int read_fd;
	int write_fd;
	int status;
	i = 0;
	int fd_file = -200;
	int fd_in = -100;
	read_fd = dup(0);
	int fd_input = -1;
	int fd_out = -2;
	int h = -50;
	char *stre;
	int h2 = -9;
	while (tmp)
	{
		// fprintf(stderr, "current cmd: %s\n", cmd_list->argv[0]);
		fd[0] = -1;
		fd[1] = -1;
		if (tmp->next_p)
		{
			pipe(fd);
			write_fd = dup(fd[1]);
			close(fd[1]);
		}
		else
		{
			write_fd = dup( 1);
		}
		g_all->ctrl_quit = 1;
		if (fork() == 0)
		{
			if(tmp != NULL && tmp->filerdr == NULL)
			{
				dup2(read_fd, 0);
				dup2(write_fd, 1);
		   		close(read_fd);
				close(write_fd);
				if (fd[0] + 1)
					close(fd[0]);
				if (fd[1] + 1)
					close(fd[1]);
			}
			else if(tmp->filerdr != NULL)
			{
				if(check_two_red(tmp) == 0)
				{
					t_filerdr *lastnamef = last_name_func(tmp);
					if(!lastnamef)
						exit(1);
					if(check_if_command_is_exist(tmp->filerdr->name, 0) == 3)
						exit(1);
					if(lastnamef->type == 0)
					{
						h = open(lastnamef->name, O_RDONLY);
						dup2(h, 0);
						dup2(write_fd, 1);
						close(h);
					}
					else if(lastnamef->type == 1)
					{
						h = open(lastnamef->name,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
						dup2(h, 1);
						dup2(read_fd, 0);
						close(h);
					}
					else if(lastnamef->type == 2)
					{
						h = open(lastnamef->name, O_CREAT|O_WRONLY|O_APPEND, 0644);
						dup2(h, 1);
						dup2(read_fd, 0);
						close(h);
					}
				}
				else if(check_two_red(tmp) == 1)
				{
					fd_out = output_ret(tmp);
					if(fd_out == -100)
						exit(1);
					fd_input = input_ret(tmp);
					if(fd_input == -100)
						exit(1);
					dup2(fd_input, 0);
					close(fd_input);
					dup2(fd_out, 1);
					close(fd_out);
				}
			}
			se_execute_command(tmp, ptr, evp);
			exit(127);
		}
		else
		{
			//parent
			close(read_fd);
			close(write_fd);
			if (tmp->next_p)
			{
				read_fd = dup(fd[0]);
				close(fd[0]);
			}
		}
		tmp = tmp->next_p;
	}
	while (wait(&g_all->staus_code) > 0);
	if (WIFSIGNALED(g_all->staus_code))
        g_all->staus_code = WTERMSIG(g_all->staus_code) + 128;
    else
        g_all->staus_code = WEXITSTATUS(g_all->staus_code) % 128;
}


void cntrol_quit(int quit)
{
	if(g_all->ctrl_quit == 1 && ft_strncmp(g_all->type, "read", 6) != 0)
	{
		write(2, "Quit: ", 7);
		ft_putnbr_fd(quit, 2);
		write(2, "\n", 1);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_history *history;
	yesdup = 0;
	t_env *evp;
	evp = malloc(sizeof(t_env));
	char *buf;
	char *ptr;
	int errcd;
	char *test;
	char 	*ret;
	buf = NULL;
	int help = 0;
	int edit = 0;
	char path[200];
	g_all = malloc(sizeof(t_commandg));
	g_all->line = NULL;
	int readinput;
	evp->my_env = copy_envp(envp);
	evp->my_env = edit_envp_shlvl(evp->my_env);
	evp->my_env = edit_envp_v(evp->my_env);
	evp->my_env = edit_envp_old_pwd(evp->my_env);
	evp->save = search_in_env2("HOME", evp->my_env);
	tgetent(NULL, getenv("TERM"));
	g_all->ctrl_c = 0;
	g_all->ctrl_quit = 0;
	g_all->staus_code = 0;
    history = new_commnd(NULL);
	while (1)
	{
		signal(SIGINT, command_c);
		signal(SIGQUIT, cntrol_quit);
		if (g_all->ctrl_c == 0)
		{
			write(1, "\033[0;33mNull37$\033[0m ", 19);
			g_all->ctrl_c = 1;
		}
		ptr = getcwd(buf, 1024);
		if(ptr != NULL)
			evp->my_env = edit_envp_pwd(ptr, evp->my_env);
		termcap_khedma(history);
		g_all->ctrl_c = 0;
		if(check_syntax_rederction(g_all->ret) == -1)
			continue;
		g_commands = parssing_shell(ptr, evp ,g_all->ret);
		g_all->ctrl_quit = 0;
		if (g_all->ret)
		{
			free(g_all->ret);
			g_all->ret = NULL;
		}
	}
}