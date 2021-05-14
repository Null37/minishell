/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:02:46 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/14 14:15:03 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

char	*half_search(char *variable, char **envp, t_norm norm)
{
	while (norm.i++ < norm.lenp)
	{
		if (my_strcmp(get_env_name(envp[norm.i]), variable) == 0)
		{
			norm.j = 0;
			while (envp[norm.i][norm.j])
			{
				if (envp[norm.i][norm.j] == '=')
				{
					norm.j += 1;
					while (envp[norm.i][norm.j])
					{
						norm.fsf[0] = envp[norm.i][norm.j];
						norm.buff = ft_strjoin(norm.buff, norm.fsf);
						norm.j++;
					}
					return (norm.buff);
				}
				norm.j++;
			}
			norm.buff = "k";
			return (norm.buff);
		}
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
	return (norm.buff);
}

