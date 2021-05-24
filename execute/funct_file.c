/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:58:35 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/24 12:59:23 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

t_history	*new_commnd(char *cmd)
{
	t_history	*h;

	h = malloc(sizeof(t_history));
	if (!cmd)
		h->cmd = NULL;
	else
		h->cmd = ft_strdup(cmd);
	h->next = NULL;
	h->preview = NULL;
	return (h);
}

void	command_pwd(char *ptr, t_env *evp)
{
	char	*ech;

	if (ptr != NULL)
	{
		write(1, ptr, strlen(ptr));
		write(1, "\n", 1);
	}
	else
	{
		ptr = search_in_env2("PWD", evp->my_env);
		if (ft_strncmp(ptr, "", 1) == 0)
			write(1, g_all->old_pwd, ft_strlen(g_all->old_pwd));
		else
			write(1, ptr, strlen(ptr));
		write(1, "\n", 1);
		free(ptr);
	}
	g_all->staus_code = 0;
}

void	command_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (is_equl(i, envp) == 1)
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void	command_echo(t_commands *tmp)
{
	int		o;
	int		i;

	o = count_arg_2(tmp);
	i = 0;
	if (o == 0 && tmp->option == 0)
		write(1, "\n", 1);
	else if (o > 0)
	{
		while (tmp->arguments[i] != NULL)
		{
			if (tmp->option == 1)
				g_all->option += ft_strlen(tmp->arguments[i]);
			ft_putchar(tmp->arguments[i]);
			if (o > 1)
			{
				g_all->option += 1;
				if(tmp->arguments[i+1] != NULL)
					write(1, " ", 1);
			}
			i++;
		}
		if (tmp->option == 0)
			write(1, "\n", 1);
	}	
	g_all->staus_code = 0;
}

void	command_in_the_sys(t_commands *tmp, char **envp)
{
	char	*error;
	int		pid;

	pid = fork();
	g_all->ctrl_quit = 1;
	g_all->type = tmp->type;
	if (pid == 0)
	{
		if (g_all->yesdup == 1)
		{
			dup2(g_all->redir_fd, 1);
			dup2(g_all->redir_fd_in, 0);
		}
		if (execve(tmp->path, tmp->all, envp) < 0)
			error_execve(tmp);
		exit(127);
	}
	else
	{
		waitpid(pid, &g_all->staus_code, 0);
		if (WIFSIGNALED(g_all->staus_code))
			g_all->staus_code = WTERMSIG(g_all->staus_code) + 128;
		else
			g_all->staus_code = WEXITSTATUS(g_all->staus_code) % 128;
	}
}
