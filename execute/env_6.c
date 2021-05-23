/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:51:00 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/23 19:06:24 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	half_add_exp(t_norm *norm, char **my_env, t_commands *tmp, int k)
{
	if (my_strcmp(my_env[norm->i], norm->varibale) == 0)
	{
		norm->j = 0;
		while (my_env[norm->i][norm->j])
		{
			if (my_env[norm->i][norm->j] == '=')
			{
				norm->j += 1;
				while (norm->tee != norm->t)
				{
					my_env[norm->i][norm->j] = tmp->arguments[k][norm->b];
					norm->j++;
					norm->b++;
					norm->tee++;
				}
				my_env[norm->i][norm->j] = '\0';
				return (-1);
			}
			norm->j++;
		}
	}
	return (0);
}

void	set_norm_exp(t_norm *norm, t_commands *tmp, int k, char **my_env)
{
	norm->lenp = 0;
	norm->j = 0;
	norm->i = 0;
	norm->b = 0;
	norm->varibale = tmp->arguments[k];
	norm->ef = search_in_env2(norm->varibale, my_env);
	norm->lenp = len_of_args(my_env);
}

void	exp_coun(t_norm *norm, t_commands *tmp, int k, char **my_env)
{
	set_norm_exp(norm, tmp, k, my_env);
	while (my_env[norm->i] != NULL)
		(norm->i)++;
}

void	set_norm_exp2(t_norm *norm, t_commands *tmp, int k, char **my_env)
{
	norm->b += 1;
	norm->te = (tmp->arguments[k] + norm->b);
	norm->tee = 0;
	norm->t = ft_strlen(norm->te);
	norm->i = -1;
}

void	add_in_exp(t_commands *tmp, int k, char **my_env)
{
	t_norm	*norm;

	norm = malloc(sizeof(t_norm));
	exp_coun(norm, tmp, k, my_env);
	if (ft_strncmp(norm->ef, "\0", 1) == 0)
		my_env[norm->i] = ft_strdup(tmp->arguments[k]);
	else
	{
		set_norm_exp2(norm, tmp, k, my_env);
		while (++norm->i < norm->lenp)
		{
			norm->g = 0;
			while (norm->varibale[norm->g])
			{
				if (norm->varibale[norm->g] == '=')
					break ;
				(norm->g)++;
			}
			if (norm->varibale[norm->g] == '\0')
				continue ;
			if (half_add_exp(norm, my_env, tmp, k) == 1)
				break ;
		}
	}
	free(norm->ef);
	free(norm);
}
