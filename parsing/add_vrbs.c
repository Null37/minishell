/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vrbs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:48:33 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/21 15:30:55 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

char	*add_vrbs_norm(char **envp, t_tmp *tamp, t_tmp *tmp, char *typ)
{
	tamp->z = -1;
	while (1)
	{
		if (!syntax(typ[++(tmp->i)], ++(tamp->z)) && tamp->z == 0)
		{
			tamp->test = my_substr(typ, tamp->k + 1, tmp->i + 1);
			tamp->test = search_in_env(tamp->test, envp);
			break ;
		}
		else if (!syntax(typ[tmp->i], tamp->z))
		{
			tamp->test = my_substr(typ, tamp->k + 1, tmp->i);
			tamp->test = search_in_env(tamp->test, envp);
			--(tmp->i);
			break ;
		}
	}
	if (tamp->test)
	{
		tamp->ss = ft_strjoin1(tamp->ss, tamp->test);
		free(tamp->test);
	}
	return (tamp->ss);
}

char	*n1_add_vrbs(char *str, t_tmp *tamp, char *typ)
{
	char	*s;

	if (typ[tamp->k + 1] == 39 || typ[tamp->k + 1] == 34)
	{
		if (!str)
		{
			return (ft_strdup(""));
		}
		else
		{
			tamp->test = ft_strdup("");
			tamp->s = ft_strjoin1(str, tamp->test);
			free(tamp->test);
			return (tamp->s);
		}
	}
	return (NULL);
}

char	*n2_add_vrbs(char *str, t_tmp *tamp, char *typ)
{
	char	*s;

	if (typ[tamp->k + 1] == '\0' || typ[tamp->k + 1] == ' '
		|| typ[tamp->k + 1] == '\\')
	{
		if (!str)
		{
			return (ft_strdup("$"));
		}
		else
		{
			tamp->test = ft_strdup("$");
			tamp->s = ft_strjoin1(str, tamp->test);
			free(tamp->test);
			return (tamp->s);
		}
	}
	return (NULL);
}

char	*add_vrbs(char **envp, char *str, t_tmp *tmp, char *typ)
{
	t_tmp	*tamp;
	char	*s;

	tamp = malloc(sizeof(t_tmp));
	tamp->k = tmp->i;
	tamp->s1 = n1_add_vrbs(str, tamp, typ);
	if (tamp->s1)
	{
		s = tamp->s1;
		free(tamp);
		return (s);
	}
	tamp->s1 = n2_add_vrbs(str, tamp, typ);
	if (tamp->s1)
	{
		s = tamp->s1;
		free(tamp);
		return (s);
	}
	tamp->ss = str;
	str = add_vrbs_norm(envp, tamp, tmp, typ);
	free(tamp);
	return (str);
}
