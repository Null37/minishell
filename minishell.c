/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:14:40 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/27 13:23:07 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

void	set_main(t_env **evp, char **buf, char **envp)
{
	*buf = NULL;
	g_all = malloc(sizeof(t_commandg));
	g_all->line = NULL;
	g_all->old_pwd = NULL;
	g_all->yesdup = 0;
	(*evp)->my_env = copy_envp(envp);
	(*evp)->my_env = edit_envp_shlvl((*evp)->my_env);
	(*evp)->my_env = edit_envp_v((*evp)->my_env);
	(*evp)->my_env = edit_envp_old_pwd((*evp)->my_env);
	(*evp)->save = search_in_env2("HOME", (*evp)->my_env);
	(*evp)->check_term = getenv("TERM");
	g_all->ctrl_c = 0;
	g_all->ctrl_quit = 0;
	g_all->staus_code = 0;
	g_all->option = 0;
}

int	half_main(char **buf, char **ptr)
{
	if (check_syntax_rederction(g_all->ret) == -1)
	{
		if (g_all->ret)
		{
			free(g_all->ret);
			g_all->ret = NULL;
		}
		free(*buf);
		free(*ptr);
		return (2);
	}
	return (0);
}

void	check_free(void)
{
	if (g_all->ret)
	{
		free(g_all->ret);
		g_all->ret = NULL;
	}
}

void	main_loop(char **buf, char **ptr, t_history **history, t_env **evp)
{
	while (1)
	{
		if (g_all->ctrl_c == 0)
		{
			write(1, "\033[0;33mNull37$\033[0m ", 19);
			g_all->ctrl_c = 1;
		}
		*ptr = getcwd(*buf, 1024);
		if (*ptr != NULL)
			(*evp)->my_env = edit_envp_pwd(*ptr, (*evp)->my_env);
		ft_putstr_fd(tgetstr("sc", NULL), STDOUT_FILENO);
		termcap_khedma(*history);
		g_all->option = 0;
		g_all->ctrl_c = 0;
		if (half_main(buf, ptr) == 2)
			continue ;
		parssing_shell(*ptr, *evp, g_all->ret);
		g_all->ctrl_quit = 0;
		check_free();
		free(*buf);
		free(*ptr);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_history	*history;
	t_env		*evp;
	char		*buf;
	char		*ptr;

	argc = 0;
	argv = 0;
	evp = malloc(sizeof(t_env));
	set_main(&evp, &buf, envp);
	if (evp->check_term == 0)
	{
		write(2, "TERM not set\n", 13);
		exit(1);
	}
	tgetent(NULL, evp->check_term);
	history = new_commnd(NULL);
	signal(SIGINT, command_c);
	signal(SIGQUIT, cntrol_quit);
	main_loop(&buf, &ptr, &history, &evp);
}
