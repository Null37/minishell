/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:50:04 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/16 10:39:52 by ssamadi          ###   ########.fr       */
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
	while (++i < lenp)
	{
		nameenv = get_env_name(envp_c[i]);
		if (my_strcmp(nameenv, "OLDPWD") == 0)
		{
			free(envp_c[i]);
			envp_c[i] = ft_strdup("OLDPWD");
			free(nameenv);
			break ;
		}
		free(nameenv);
	}
	return (envp_c);
}

char	**edit_envp_pwd(char *ptr, char **envp_c)
{		
	t_norm	norm;

	norm.lenp = len_of_args(envp_c);
	norm.i = -1;
	while (++norm.i < norm.lenp)
	{
		norm.nameenv = get_env_name(envp_c[norm.i]);
		if (my_strcmp(norm.nameenv, "PWD") == 0)
		{
			free(envp_c[norm.i]);
			norm.j = ft_strlen(norm.nameenv);
			norm.s = ft_strjoin1(norm.nameenv, "=");
			norm.s = ft_strjoin1(norm.s, ptr);
			envp_c[norm.i] = norm.s;
			break ;
		}
		free(norm.nameenv);
	}
	return (envp_c);
}

char	**half_v_edit(char **envp_c, t_norm norm)
{
	while (++norm.i < norm.lenp)
	{
		norm.nameenv = get_env_name(envp_c[norm.i]);
		if (my_strcmp(norm.nameenv, "_") == 0)
		{
			norm.j = 0;
			while (envp_c[norm.i][norm.j])
			{
				if (envp_c[norm.i][norm.j] == '=')
				{
					norm.j += 1;
					while (norm.tee != norm.t)
					{
						envp_c[norm.i][norm.j] = norm.v[norm.tee];
						norm.j++;
						norm.tee++;
					}
					envp_c[norm.i][norm.j] = '\0';
					free(norm.nameenv);
					return (envp_c);
				}
				norm.j++;
			}
		}
		free(norm.nameenv);
	}
	return (envp_c);
}

char	**edit_envp_v(char **envp_c)
{
	t_norm	norm;

	norm.v = "./minishell";
	norm.lenp = len_of_args(envp_c);
	norm.t = ft_strlen(norm.v);
	norm.tee = 0;
	norm.i = -1;
	envp_c = half_v_edit(envp_c, norm);
	return (envp_c);
}
