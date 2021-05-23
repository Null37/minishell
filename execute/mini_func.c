/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:02:50 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/23 11:57:54 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	ft_isdigit2(char number)
{
	if (number >= '0' && number <= '9')
	{
		return (1);
	}
	else
		return (0);
}

int	is_equl(int i, char **envp)
{
	int	j;

	j = 0;
	while (envp[i] && envp[i][j])
	{
		if (envp[i][j] == '=')
			return (1);
		j++;
	}
	return (0);
}

int	len_of_args(char **args)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

void	error_syn(t_commands *tmp, int k)
{
	write(2, "minishell: ", 11);
	write(2, "export: ", 7);
	write(2, "`", 1);
	write(2, tmp->arguments[k], strlen(tmp->arguments[k]));
	write(2, "'", 1);
	write(2, ": ", 2);
	write(2, "not a valid identifier", 22);
	write(2, "\n", 1);
}

int	syntax_true(t_commands *tmp, char **envp, int k, int lenarg)
{
	int	i;

	i = 0;
	while (tmp->arguments[k][i])
	{
		if (tmp->arguments[k][0] == '=')
		{
			error_syn(tmp, k);
			g_all->staus_code = 1;
			return (1);
		}
		if (tmp->arguments[k][i] == '=')
		{
			if (check_syntax_export_true(tmp, k, lenarg) == 0)
				add_in_env(tmp, k, envp);
			return (1);
		}
		i++;
	}
	return (0);
}
