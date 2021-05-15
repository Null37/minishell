/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:54:51 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/15 16:03:50 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	half_unset(int j, int lenp, t_env *evp)
{
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
	while (k++ < lenarg)
	{
		check_syntax(tmp, k, lenarg, 'u');
		while (i++ < lenp)
		{
			if (strncmp(evp->my_env[i], tmp->arguments[k],
					strlen(tmp->arguments[k])) == 0)
			{
				j = i;
				half_unset(j, lenp, evp);
				lenp = len_of_args(evp->my_env);
			}
		}
	}
}
