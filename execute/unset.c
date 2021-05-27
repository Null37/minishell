/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:54:51 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/27 12:48:07 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	half_unset(int j, int lenp, t_env *evp)
{
	free(evp->my_env[j]);
	while (j < lenp - 1)
	{
		evp->my_env[j] = evp->my_env[j + 1];
		j++;
	}
	evp->my_env[j] = NULL;
}

void	command_unset(t_commands *tmp, t_env *evp)
{
	int		lenp;
	int		lenarg;
	int		k;
	int		i;
	int		j;

	i = -1;
	k = -1;
	lenp = len_of_args(evp->my_env);
	lenarg = count_arg_2(tmp);
	while (++k < lenarg)
	{
		check_syntax(tmp, k, 'u');
		while (++i < lenp)
		{
			if (ft_strncmp(evp->my_env[i], tmp->arguments[k],
					ft_strlen(tmp->arguments[k])) == 0)
			{
				j = i;
				half_unset(j, lenp, evp);
				lenp = len_of_args(evp->my_env);
			}
		}
	}
}

t_norm	*new_norm(char **envp_c)
{
	t_norm	*norm;

	norm = malloc(sizeof(t_norm));
	norm->lenp = len_of_args(envp_c);
	norm->o = 0;
	norm->i = -1;
	return (norm);
}

char	**set_norm(t_norm *norm, char *ptr, char **envp_c)
{
	norm->len = ft_strlen(ptr);
	norm->j = ft_strlen(norm->nameenv);
	envp_c[norm->i] = (char *)malloc(norm->len + norm->j + 1 + 2);
	norm->t = 0;
	return (envp_c);
}
