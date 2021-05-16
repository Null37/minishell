/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:14:24 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/16 13:10:16 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	half_export(t_commands *tmp, t_env *evp, t_norm norm)
{
	norm.k = 0;
	while (norm.k < norm.lenarg)
	{
		if (syntax_true(tmp, evp->my_env, norm.k, norm.lenarg) == 0)
		{
			if (check_syntax_export_false(tmp, norm.k, norm.lenarg) == 0)
				add_in_exp(tmp, norm.k, evp->my_env);
		}
		norm.k++;
	}
}

void	command_export(t_commands *tmp, t_env *evp)
{
	t_norm	norm;

	norm.o = count_arg_2(tmp);
	evp->my_env = sort_algo(evp->my_env);
	norm.lenarg = norm.o;
	if (norm.o == 0)
		add_double_quotes(evp->my_env);
	else if (norm.o > 0)
	{
		norm.lenp = len_of_args(evp->my_env);
		norm.tprr = malloc(sizeof(char *) * (norm.lenp + norm.o + 1));
		norm.tprr[norm.lenp + norm.o] = NULL;
		norm.z = -1;
		while (norm.tprr[++norm.z] != NULL)
			norm.tprr[norm.z] = NULL;
		norm.z = -1;
		while (evp->my_env[++norm.z] != NULL)
			norm.tprr[norm.z] = evp->my_env[norm.z];
		free(evp->my_env);
		evp->my_env = norm.tprr;
		half_export(tmp, evp, norm);
	}
	g_all->staus_code = 0;
}
