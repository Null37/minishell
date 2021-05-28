/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:52:12 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/28 13:11:57 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	half_write(char **my_env, int i, int j)
{
	while (my_env[i][j])
	{
		if (my_env[i][j] == '\\' || my_env[i][j] == '$' || my_env[i][j] == 34)
			write(1, "\\", 1);
		write(1, &my_env[i][j], 1);
		j++;
	}
}

void	ok_write(char **my_env, int i, int j)
{
	int	b;

	b = 0;
	write(1, "declare -x ", 11);
	while (my_env[i][j])
	{
		if (my_env[i][j] == '=')
		{
			write(1, "=", 1);
			b = 1;
			write(1, "\"", 1);
			j++;
			break ;
		}
		else
			write(1, &my_env[i][j], 1);
		j++;
	}
	half_write(my_env, i, j);
	if (b == 1)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

void	add_double_quotes(char **my_env)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (my_env[i] != NULL)
	{
		j = 0;
		while (my_env[i][j])
		{
			if (my_env[i][j] != '=')
			{
				ok_write(my_env, i, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	count_arg_2(t_commands *tmp)
{
	int	i;
	int	cpt;

	i = -1;
	cpt = 0;
	while (tmp->arguments[++i] != NULL)
		cpt++;
	return (cpt);
}

void	ft_putchar(char *str)
{
	write(1, str, strlen(str));
}
