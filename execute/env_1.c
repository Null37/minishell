/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:50:04 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/14 13:08:12 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

char	**edit_envp_old_pwd(char **envp_c)
{
	char	*nameenv;
	int		lenp;
	int		i;

	i = -1;
	lenp = len_of_args(envp_c);
	while (i++ < lenp)
	{
		nameenv = get_env_name(envp_c[i]);
		if (my_strcmp(nameenv, "OLDPWD") == 0)
		{
			free(envp_c[i]);
			envp_c[i] = ft_strdup("OLDPWD");
			break ;
		}
	}
	return (envp_c);
}

char	**edit_envp_pwd(char *ptr, char **envp_c)
{		
	t_norm norm;

	norm.lenp = len_of_args(envp_c);
	norm.i = -1;
	while (norm.i++ < norm.lenp)
	{
		norm.nameenv = get_env_name(envp_c[norm.i]);
		if (my_strcmp(norm.nameenv, "PWD") == 0)
		{
			free(envp_c[norm.i]);
			norm.j = ft_strlen(norm.nameenv);
			norm.s = ft_strjoin1(norm.nameenv, "=");
			norm.s = ft_strjoin1(norm.s, ptr);
			envp_c[norm.i] = norm.s;
			break;
		}
	}
		return (envp_c);
}
