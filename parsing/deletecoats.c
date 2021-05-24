/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletecoats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:48:58 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/24 18:45:56 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	norm_deletcoats(char **envp, char *str, t_tmp	*tmp)
{
	if (str[tmp->i] == '\\')
	{
		tmp->s1[0] = str[tmp->i + 1];
		tmp->rstr = ft_strjoin1(tmp->rstr, tmp->s1);
		(tmp->i)++;
		return (1);
	}
	if (str[tmp->i] == 34)
	{
		tmp->rstr = getdblcoat(envp, tmp->rstr, str, tmp);
		return (1);
	}
	if (str[tmp->i] == 39)
	{
		tmp->rstr = getsglcoat(tmp->rstr, str, tmp);
		return (1);
	}
	return (0);
}

int	norm_deletcoats1(char **envp, char *str, t_tmp *tmp)
{
	if (str[tmp->i] == '$' && str[tmp->i + 1] == '?')
	{
		tmp->ss = ft_itoa(g_all->staus_code);
		tmp->rstr = ft_strjoin1(tmp->rstr, tmp->ss);
		free(tmp->ss);
		tmp->i++;
		return (1);
	}
	if (str[tmp->i] == '$')
	{
		tmp->rstr = add_vrbs(envp, tmp->rstr, tmp, str);
		return (1);
	}
	return (0);
}
char	*free_ret(t_tmp	*tmp)
{
	char *s;

	s = tmp->rstr;
	free(tmp->s1);
	free(tmp);
	return (s);
}
char	*deletecoats(char **envp, char *str)
{
	t_tmp	*tmp;

	tmp = malloc(sizeof(t_tmp));
	tmp->s1 = malloc(2);
	tmp->s1[1] = '\0';
	tmp->i = -1;
	tmp->j = 0;
	tmp->rstr = NULL;
	while (str[++(tmp->i)])
	{
		if (norm_deletcoats(envp, str, tmp))
			continue ;
		if (norm_deletcoats1(envp, str, tmp))
			continue ;
		tmp->s1[0] = str[tmp->i];
		tmp->rstr = ft_strjoin1(tmp->rstr, tmp->s1);
		tmp->j++;
	}
	free(str);
	return (free_ret(tmp));
}
