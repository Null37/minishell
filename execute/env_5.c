/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:14:24 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/15 13:19:43 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	command_export(t_commands *tmp, t_env *evp)
{
	int o = count_arg_2(tmp);
	int i = 0;
	int lenarg;
	char *s;
	int k = 0;
	int z;
	evp->my_env = sort_algo(evp->my_env);
	lenarg = o;
	if (o == 0)
		add_double_quotes(evp->my_env);
	else if (o > 0)
	{
		char **tprr;
		int lenp = len_of_args(evp->my_env);
		tprr = malloc(sizeof(char*) * (lenp + o + 1));
		tprr[lenp + o] = NULL;
		z = -1;
		while(tprr[++z] != NULL)
			tprr[z] = NULL;
		z = -1;
		while(evp->my_env[++z] != NULL)
		{
			tprr[z] = evp->my_env[z];
		}
		free(evp->my_env);
		evp->my_env = tprr;
		while (k < lenarg)
		{
			if (syntax_true(tmp, evp->my_env, k, lenarg) == 0)
			{
				if (check_syntax_export_false(tmp ,k, lenarg) == 0)
					add_in_exp(tmp,k, evp->my_env);
			}
			k++;
		}
	}
	g_all->staus_code = 0;
}
