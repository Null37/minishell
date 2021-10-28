/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:27:47 by fbouibao          #+#    #+#             */
/*   Updated: 2021/06/12 13:09:30 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

void	key_up_cnt(t_history **h_tmp)
{
	if ((*h_tmp)->cmd)
	{
		write(1, (*h_tmp)->cmd, ft_strlen((*h_tmp)->cmd));
		free(g_all->ret);
		g_all->ret = ft_strdup((*h_tmp)->cmd);
	}
	g_all->termcap_mod = 0;
}

int	key_up(t_history **history, int d, t_history **h_tmp, int a)
{
	if (d == KEY_UP)
	{
		if (g_all->termcap_mod == 4)
			get_last_cmd(history, h_tmp);
		if ((*history)->cmd == NULL && g_all->line && !(*h_tmp)->preview)
			return (1);
		a = 8 + g_all->option;
		tputs(tgoto(tgetstr("ch", NULL), 0, a), 1, ft_putc);
		tputs(tgetstr("rc", NULL), 1, ft_putc);
		ft_putstr_fd(tgetstr("cd", NULL), STDOUT_FILENO);
		if ((*h_tmp) && (*h_tmp)->preview)
		{
			if (g_all->termcap_mod == 1)
				(*h_tmp) = (*h_tmp)->preview;
			write_key_up(h_tmp);
			g_all->ret = ft_strdup((*h_tmp)->cmd);
			g_all->termcap_mod = 1;
		}
		else if (!(*h_tmp)->preview)
			key_up_cnt(h_tmp);
	}
	return (0);
}

void	key_down(t_history	**h_tmp, int d)
{
	if (d == KEY_DOWN)
	{
		if (g_all->termcap_mod == 4)
			get_last_cmd2(h_tmp);
		tputs(tgoto(tgetstr("ch", NULL), 0, (8 + g_all->option)), 1, ft_putc);
		tputs(tgetstr("rc", NULL), 1, ft_putc);
		ft_putstr_fd(tgetstr("cd", NULL), STDOUT_FILENO);
		if ((*h_tmp) && (*h_tmp)->next)
		{
			(*h_tmp) = (*h_tmp)->next;
			write(1, (*h_tmp)->cmd, ft_strlen((*h_tmp)->cmd));
			free(g_all->ret);
			g_all->ret = ft_strdup((*h_tmp)->cmd);
			g_all->termcap_mod = 1;
		}
		else
			key_down_cnt();
	}
}

int	key_enter(int d, t_history **history, t_history **h_tmp)
{
	if (d == ENTER)
	{
		g_all->termcap_mod = 0;
		free_n_enter();
		if (g_all->ret == NULL)
		{
			write(1, "\033[0;33mNull37$\033[0m ", 19);
			ft_putstr_fd(tgetstr("sc", NULL), STDOUT_FILENO);
		}
		if (g_all->ret != NULL)
		{
			if ((*history)->cmd == NULL)
				(*history)->cmd = ft_strdup(g_all->ret);
			else
			{
				(*h_tmp) = (*history);
				(*history)->next = new_commnd(g_all->ret);
				(*history) = (*history)->next;
				(*history)->preview = (*h_tmp);
			}
			return (1);
		}
		return (2);
	}
	return (0);
}

int	half_termcap(int d)
{
	d = get_char();
	if (d == CTRL_D)
	{
		if (g_all->ret == NULL)
		{
			write(1, "exit\n", 5);
			return (-666);
		}
	}
	else if (d >= 32 && d < 127)
	{
		g_all->ret = ft_strjoinchar(g_all->ret, d);
		free(g_all->line);
		g_all->line = ft_strdup(g_all->ret);
		write(1, &d, 1);
	}
	return (d);
}
