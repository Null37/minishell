/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:54:51 by ssamadi           #+#    #+#             */
/*   Updated: 2021/06/12 13:23:35 by ssamadi          ###   ########.fr       */
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

int	cnt_unset(t_commands *tmp, t_env *evp, int k)
{
	int		i;
	char	*name;
	int		lenp;

	i = -1;
	lenp = len_of_args(evp->my_env);
	while (++i < lenp)
	{
		name = get_env_name(evp->my_env[i]);
		if (ft_strncmp(name, tmp->arguments[k],
				ft_strlen(tmp->arguments[k]) + 1) == 0)
		{
			half_unset(i, lenp, evp);
			lenp = len_of_args(evp->my_env);
			free(name);
			name = NULL;
			return (1);
		}
		free(name);
		name = NULL;
	}
	return (0);
}

void	command_unset(t_commands *tmp, t_env *evp)
{
	int		lenarg;
	int		k;

	k = -1;
	lenarg = count_arg_2(tmp);
	while (++k < lenarg)
	{
		check_syntax(tmp, k, 'u');
		cnt_unset(tmp, evp, k);
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
