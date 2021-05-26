/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_fl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:48:04 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/26 20:43:01 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

char	*ft_strjoinchar(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	if (s == NULL)
	{
		str = (char *)malloc(2);
		if (str == NULL)
			return (0);
		str[0] = c;
		str[1] = '\0';
		return (str);
	}
	while (s[i])
		i++;
	str = (char *)malloc(i + 2);
	if (str == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}

int ft_putc(int s)
{
	return write(1,&s,1);
}

int	get_char()
{
	char    c;
	int		total;
	struct termios old;
	struct	termios term;

	tcgetattr(0, &old);
	term = old;
	term.c_lflag &= ~(ICANON|ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	while (read(0, &c, 1) <= 0);
	total += c;
	while (read(0, &c, 1) > 0)
			total += c;
	tcsetattr(0, TCSANOW, &old);
	return (total);
}

char	*termcap_khedma(t_history *history)
{
	int			d;
	char		*s;
	t_history	*h_tmp;
	static int	i;
	int a;

	while(1)
	{
		if (history->next == NULL)
			break ;
		history = history->next;
	}
	h_tmp = history;
	g_all->line = NULL;
	g_all->ret = NULL;
	while(1)
	{
		d = get_char();
		if (d == 4)
		{
			if (g_all->ret ==  NULL)
			{
				write(1,"exit",4);
				exit(0);
			}
		}
		else if (d >= 32 && d < 127)
		{
			g_all->ret = ft_strjoinchar(g_all->ret, d);
			free(g_all->line);
			g_all->line = ft_strdup(g_all->ret);
			write(1, &d ,1);
		}
		else if (d == KEY_REMOVE)
		{
			int i;
			i = 0;
			if (ft_strlen(g_all->ret) > 0)
			{
				while (i < (ft_strlen(g_all->ret) - 1))
					i++;
				g_all->ret[i] = '\0';
				tputs(tgetstr("le",NULL), 1, ft_putc);
				tputs(tgetstr("dc",NULL), 1, ft_putc);
			}
			if(ft_strlen(g_all->ret) == 0)
			{
				free(g_all->ret);
				g_all->ret = NULL;
			}
		}
		else if (d == KEY_DOWN)
		{
			a = 8 + g_all->option;
			tputs(tgoto(tgetstr("ch", NULL), 0, a), 1, ft_putc);
			tputs(tgetstr("rc",NULL), 1, ft_putc);
			ft_putstr_fd(tgetstr("cd", NULL), STDOUT_FILENO);
			if (h_tmp && h_tmp->next)
			{
				h_tmp = h_tmp->next;
				write(1, h_tmp->cmd, ft_strlen(h_tmp->cmd));
				free(g_all->ret);
				g_all->ret = ft_strdup(h_tmp->cmd);
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
		else if (d == KEY_UP)
		{
			if (history->cmd == NULL && g_all->line && !h_tmp->preview)
				continue ;
			int a = 8 + g_all->option;
			tputs(tgoto(tgetstr("ch", NULL), 0, a), 1, ft_putc);
			tputs(tgetstr("rc",NULL), 1, ft_putc);
			ft_putstr_fd(tgetstr("cd", NULL), STDOUT_FILENO);

			if (h_tmp && h_tmp->preview)
			{
				write(1, h_tmp->cmd, ft_strlen(h_tmp->cmd));
				free(g_all->ret);
				g_all->ret = ft_strdup(h_tmp->cmd);
				h_tmp = h_tmp->preview;
			}
			else if (!h_tmp->preview)
			{
				if (h_tmp->cmd)
				{
					write(1, h_tmp->cmd, ft_strlen(h_tmp->cmd));
					free(g_all->ret);
					g_all->ret = ft_strdup(h_tmp->cmd);
				}
			}
		}
		else if (d == ENTER)
		{
			free(g_all->line);
			g_all->line = NULL;
			write(1,"\n",1);
			if(g_all->ret == NULL)
			{
				write(1, "\033[0;33mNull37$\033[0m ", 19);
				ft_putstr_fd(tgetstr("sc", NULL), STDOUT_FILENO);
			}
			if (g_all->ret != NULL)
			{
				if (history->cmd == NULL)
					history->cmd = ft_strdup(g_all->ret);
				else
				{
					h_tmp = history;
					history->next = new_commnd(g_all->ret);
					history = history->next;
					history->preview = h_tmp;
				}
				return (g_all->ret);
			}
			continue ;
		}
	}
}
