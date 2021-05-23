/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:07:58 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/23 18:50:35 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

void	sort_algo(t_env *evp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (evp->my_env[j] != NULL)
	{
		i = 0;
		while (evp->my_env[i] != NULL)
		{
			if (ft_strncmp(evp->my_env[i], evp->my_env[j], ft_strlen(evp->my_env[j])) > 0)
			{
				tmp = evp->my_env[i];
				evp->my_env[i] = evp->my_env[j];
				evp->my_env[j] = tmp;
			}
			i++;
		}
		j++;
	}
}
