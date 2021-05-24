/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coats_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:20:32 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/24 18:44:36 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	norm_getdbc(char **envp, char **rstr, char *str, t_tmp *tmp)
{
	char	*ss;

	if (str[tmp->i] == '\\' && str[tmp->i + 1] == '$')
	{
		*rstr = ft_strjoinchar(*rstr, '$');
		tmp->i++;
		return (1);
	}
	if (str[tmp->i] == '$' && str[tmp->i + 1] == '?')
	{
		ss = ft_itoa(g_all->staus_code);
		*rstr = ft_strjoin1(*rstr, ss);
		free(ss);
		tmp->i++;
		return (1);
	}
	if (str[tmp->i] == '$')
	{
		*rstr = add_vrbs(envp, *rstr, tmp, str);
		return (1);
	}
	return (0);
}

char	*getdblcoat(char **envp, char *rstr, char *str, t_tmp *tmp)
{
	while (str[++(tmp->i)])
	{
		if (norm_getdbc(envp, &rstr, str, tmp))
			continue ;
		if (str[tmp->i] == '\\'
			&& (str[tmp->i + 1] == '\\' || str[tmp->i + 1] == 34))
		{
			tmp->s1[0] = str[tmp->i + 1];
			rstr = ft_strjoin1(rstr, tmp->s1);
			(tmp->i)++;
			continue ;
		}
		if (str[tmp->i] == 34)
			break ;
		tmp->s1[0] = str[tmp->i];
		rstr = ft_strjoin1(rstr, tmp->s1);
		
	}
	return (rstr);
}

char	*getsglcoat(char *rstr, char *str, t_tmp *tmp)
{
	while (str[++(tmp->i)])
	{
		if (str[tmp->i] == 39)
			break ;
		tmp->s1[0] = str[tmp->i];
		rstr = ft_strjoin1(rstr, tmp->s1);
	}
	return (rstr);
}
