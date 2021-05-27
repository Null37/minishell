/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:27:47 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/27 13:01:16 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

int	key_up(t_history **history, int d, t_history **h_tmp, int a)
{
	if (d == KEY_UP)
	{
		if ((*history)->cmd == NULL && g_all->line && !(*h_tmp)->preview)
			return (1);
		a = 8 + g_all->option;
		tputs(tgoto(tgetstr("ch", NULL), 0, a), 1, ft_putc);
		tputs(tgetstr("rc", NULL), 1, ft_putc);
		ft_putstr_fd(tgetstr("cd", NULL), STDOUT_FILENO);
		if ((*h_tmp) && (*h_tmp)->preview)
		{
			write_key_up(h_tmp);
			g_all->ret = ft_strdup((*h_tmp)->cmd);
			(*h_tmp) = (*h_tmp)->preview;
		}
		else if (!(*h_tmp)->preview)
		{
			if ((*h_tmp)->cmd)
			{
				write(1, (*h_tmp)->cmd, ft_strlen((*h_tmp)->cmd));
				free(g_all->ret);
				g_all->ret = ft_strdup((*h_tmp)->cmd);
			}
		}
	}
	return (0);
}

void	key_down(t_history	**h_tmp, int d)
{
	int	a;

	if (d == KEY_DOWN)
	{
		a = 8 + g_all->option;
		tputs(tgoto(tgetstr("ch", NULL), 0, a), 1, ft_putc);
		tputs(tgetstr("rc", NULL), 1, ft_putc);
		ft_putstr_fd(tgetstr("cd", NULL), STDOUT_FILENO);
		if ((*h_tmp) && (*h_tmp)->next)
		{
			(*h_tmp) = (*h_tmp)->next;
			write(1, (*h_tmp)->cmd, ft_strlen((*h_tmp)->cmd));
			free(g_all->ret);
			g_all->ret = ft_strdup((*h_tmp)->cmd);
		}
		else
		{
			free(g_all->ret);
			if (g_all->line)
				g_all->ret = ft_strdup(g_all->line);
			else
				g_all->ret = NULL;
			write(1, g_all->ret, ft_strlen(g_all->ret));
		}
	}
}

void	key_remove(int d)
{
	int	i;

	i = 0;
	if (d == KEY_REMOVE)
	{
		if (ft_strlen(g_all->ret) > 0)
		{
			while (i < ((int)ft_strlen(g_all->ret) - 1))
				i++;
			g_all->ret[i] = '\0';
			tputs(tgetstr("le", NULL), 1, ft_putc);
			tputs(tgetstr("dc", NULL), 1, ft_putc);
		}
		if (ft_strlen(g_all->ret) == 0)
		{
			free(g_all->ret);
			g_all->ret = NULL;
		}
	}
}

int	key_enter(int d, t_history **history, t_history **h_tmp)
{
	if (d == ENTER)
	{
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
			write(1, "exit", 4);
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
