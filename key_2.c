/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:33:39 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/28 16:12:58 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

int	half_join_char(char *s, char c, char **str)
{
	if (s == NULL)
	{
		*str = (char *)malloc(2);
		if (*str == NULL)
			return (0);
		str[0][0] = c;
		str[0][1] = '\0';
		return (1);
	}
	return (-1);
}

char	*ft_strjoinchar(char *s, char c)
{
	int		i;
	char	*str;
	int		r;

	i = 0;
	r = half_join_char(s, c, &str);
	if (r == 1)
		return (str);
	else if (r == 0)
		return (NULL);
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

char	*termcap_khedma(t_history *history)
{
	t_history	*h_tmp;
	int			a;
	int			tm;

	tm = 0;
	a = 0;
	while (1)
	{
		if (history->next == NULL)
			break ;
		history = history->next;
	}
	h_tmp = history;
	g_all->line = NULL;
	g_all->ret = NULL;
	return (loop_termcap(&history, &h_tmp, tm, a));
}

void	old_pwd(t_env *evp)
{
	evp->test = search_in_env2("PWD", evp->my_env);
	if (ft_strncmp(evp->test, "", 1) != 0)
		g_all->old_pwd = search_in_env2("PWD", evp->my_env);
	free(evp->test);
}
