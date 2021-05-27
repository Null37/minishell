/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_fl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:48:04 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/27 13:01:26 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

int	ft_putc(int s)
{
	return (write(1, &s, 1));
}

int	get_char(void)
{
	char			c;
	int				total;
	struct termios	old;
	struct termios	term;

	tcgetattr(0, &old);
	term = old;
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	while (read(0, &c, 1) <= 0)
		continue ;
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &old);
	return (total);
}

void	write_key_up(t_history **h_tmp)
{
	write(1, (*h_tmp)->cmd, ft_strlen((*h_tmp)->cmd));
	free(g_all->ret);
}

void	free_n_enter(void)
{
	free(g_all->line);
	g_all->line = NULL;
	write(1, "\n", 1);
}

char	*loop_termcap(t_history **history, t_history **h_tmp, int tm, int a)
{
	int	d;

	d = 0;
	while (1)
	{
		d = half_termcap(d);
		if (d == -666)
			exit(0);
		key_remove(d);
		key_down(h_tmp, d);
		if (key_up(history, d, h_tmp, a) == 1)
			continue ;
		tm = key_enter(d, history, h_tmp);
		if (tm == 1)
			return (g_all->ret);
		else if (tm == 2)
			continue ;
	}
	return (NULL);
}
