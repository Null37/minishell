/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:02:46 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/16 12:51:25 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

char	*half_h_search(char *variable, char **envp, t_norm norm)
{
	norm.j += 1;
	while (envp[norm.i][norm.j])
	{
		norm.fsf[0] = envp[norm.i][norm.j];
		norm.buff = ft_strjoin1(norm.buff, norm.fsf);
		norm.j++;
	}
	return (norm.buff);
}

char	*half_search(char *variable, char **envp, t_norm norm)
{
	char	*tmp;

	while (++norm.i < norm.lenp)
	{
		tmp = get_env_name(envp[norm.i]);
		if (my_strcmp(tmp, variable) == 0)
		{
			norm.j = 0;
			while (envp[norm.i][norm.j])
			{
				if (envp[norm.i][norm.j] == '=')
				{
					norm.buff = half_h_search(variable, envp, norm);
					free(tmp);
					return (norm.buff);
				}
				norm.j++;
			}
			norm.buff = "k";
			free(tmp);
			return (norm.buff);
		}
		free(tmp);
	}
	return (norm.buff);
}

char	*search_in_env2(char *variable, char **envp)
{
	t_norm	norm;

	norm.j = 0;
	norm.fsf = ft_strdup(" ");
	norm.buff = ft_strdup("");
	norm.lenp = len_of_args(envp);
	norm.i = -1;
	norm.buff = half_search(variable, envp, norm);
	free(norm.fsf);
	return (norm.buff);
}

char	**half_edit_old(char *ptr, char **envp_c, t_norm *norm)
{
	norm->h = 0;
	while (norm->j > 0)
	{
		envp_c[norm->i][norm->h] = norm->nameenv[norm->o];
		norm->o++;
		norm->h++;
		norm->j--;
	}
	norm->j = ft_strlen(norm->nameenv);
	envp_c[norm->i][norm->j] = '=';
	while (norm->len > 0)
	{
		norm->j++;
		envp_c[norm->i][norm->j] = ptr[norm->t];
		norm->t++;
		norm->len--;
	}
	return (envp_c);
}

char	**edit_evp_new_oldpwd(char *ptr, char **envp_c)
{
	t_norm	*norm;

	norm = new_norm(envp_c);
	while (++norm->i < norm->lenp)
	{
		norm->nameenv = get_env_name(envp_c[norm->i]);
		if (my_strcmp(norm->nameenv, "OLDPWD") == 0)
		{
			free(envp_c[norm->i]);
			envp_c = set_norm(norm, ptr, envp_c);
			while (1)
			{
				envp_c = half_edit_old(ptr, envp_c, norm);
				free(norm->nameenv);
				break ;
			}
			envp_c[norm->i][norm->j + 1] = '\0';
			break ;
		}
		free(norm->nameenv);
	}
	free(norm);
	return (envp_c);
}
