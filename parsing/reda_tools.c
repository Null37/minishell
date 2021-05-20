/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reda_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:53:02 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/20 11:57:03 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	nbr_argts(t_commands *commands)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = -1;
	if (!check_cmd(commands->command))
		return (0);
	while (1)
	{
		if (commands->command[++i] == 34)
			skip_double_coats(commands->command, &i);
		else if (commands->command[i] == 39)
			skip_single_coats(commands->command, &i);
		else if (commands->command[i] == '\\')
		{
			i++;
			continue ;
		}
		if (commands->command[i] == ' ' && commands->command[i + 1] != ' ')
			cpt++;
		if (!commands->command[i])
			break ;
	}
	cpt++;
	return (cpt);
}

int	nbr_argts2(char *command)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = -1;
	if (!check_cmd(command))
		return (0);
	while (1)
	{
		if (command[++i] == 34)
			skip_double_coats(command, &i);
		else if (command[i] == 39)
			skip_single_coats(command, &i);
		else if (command[i] == '\\')
		{
			i++;
			continue ;
		}
		if (command[i] == ' ' && command[i + 1] != ' ')
			cpt++;
		if (!command[i])
			break ;
	}
	cpt++;
	return (cpt);
}

void	add_null(t_commands *cmd, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
	{
		cmd->all[i] = NULL;
	}
	i = -1;
	while (++i < nbr - 1)
	{
		cmd->arguments[i] = NULL;
	}
}

int	check_cmd(char *cmnd)
{
	int	i;

	i = -1;
	if (!cmnd)
		return (0);
	while (cmnd[++i])
	{
		if (cmnd[i] != ' ')
			return (1);
	}
	return (0);
}

int	check_echo_n(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] != '-')
		return (1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (1);
	}
	return (0);
}
