/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:07:58 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/14 16:37:25 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

char **sort_algo(char **sortest)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j= 0;
	while(sortest[j] != NULL)
	{
		i = 0;
		while (sortest[i] != NULL)
		{
			if(ft_strncmp(sortest[i], sortest[j], ft_strlen(sortest[j])) > 0)
			{
				tmp = sortest[i];
				sortest[i] = NULL;
				sortest[i] = sortest[j];
				sortest[j] = NULL;
				sortest[j] = tmp;
			}
			i++;
		}
		
		j++;
	}
	return (sortest);
}
