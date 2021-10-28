/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 13:02:51 by fbouibao          #+#    #+#             */
/*   Updated: 2021/06/12 13:09:45 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

void	get_last_cmd(t_history **history, t_history **h_tmp)
{
	while (1)
	{
		if ((*history)->next == NULL)
			break ;
		(*history) = (*history)->next;
	}
	*h_tmp = *history;
	g_all->termcap_mod = 0;
}

void	get_last_cmd2(t_history **h_tmp)
{
	while (1)
	{
		if ((*h_tmp)->next == NULL)
			break ;
		(*h_tmp) = (*h_tmp)->next;
	}
	g_all->termcap_mod = 0;
}

void	key_down_cnt(void)
{
	free(g_all->ret);
	if (g_all->line)
		g_all->ret = ft_strdup(g_all->line);
	else
		g_all->ret = NULL;
	write(1, g_all->ret, ft_strlen(g_all->ret));
	g_all->termcap_mod = 0;
}
