/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 12:58:09 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/24 16:53:05 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	command_c(int signum)
{
	g_all->staus_code = 1;
	write(1, "\n", 1);
	write(1, "\033[0;33mNull37$\033[0m ", 19);
	ft_putstr_fd(tgetstr("sc", NULL), STDOUT_FILENO);
	if (g_all->ret)
	{
		free(g_all->ret);
		g_all->ret = NULL;
	}
	g_all->ctrl_c = 1;
}

void	cntrol_quit(int quit)
{
	if (g_all->ctrl_quit == 1 && ft_strncmp(g_all->type, "read", 6) != 0)
	{
		write(2, "Quit: ", 7);
		ft_putnbr_fd(quit, 2);
		write(2, "\n", 1);
	}
}
