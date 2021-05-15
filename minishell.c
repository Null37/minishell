/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:14:40 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/15 15:36:43 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

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