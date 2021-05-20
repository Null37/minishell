/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:14:40 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/20 17:33:31 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

int main(int argc, char **argv, char **envp)
{
	t_history *history;
	t_env *evp;
	char *buf;
	char *ptr;

	evp = malloc(sizeof(t_env));
	buf = NULL;
	g_all = malloc(sizeof(t_commandg));
	g_all->line = NULL;
	g_all->yesdup = 0;
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
		if (ptr != NULL)
			evp->my_env = edit_envp_pwd(ptr, evp->my_env);
		termcap_khedma(history);
		g_all->ctrl_c = 0;
		if (check_syntax_rederction(g_all->ret) == -1)
			continue ;
		parssing_shell(ptr, evp ,g_all->ret);
		g_all->ctrl_quit = 0;
		if (g_all->ret)
		{
			free(g_all->ret);
			g_all->ret = NULL;
		}
		free(buf);
		free(ptr);
	}
}
