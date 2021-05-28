/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:00:12 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/28 12:26:45 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	skip_filename(char *cmds, int *i)
{
	while (cmds[++(*i)])
		if (cmds[*i] != '>' && cmds[*i] != '<' && cmds[*i] != ' ')
			break ;
	while (*i < (int)ft_strlen(cmds))
	{
		if (cmds[*i] == 34)
			skip_double_coats(cmds, i);
		else if (cmds[*i] == 39)
			skip_single_coats(cmds, i);
		else if (cmds[*i] == '\\')
		{
			(*i) += 2;
			continue ;
		}
		if (cmds[*i] == '>' || cmds[*i] == '<'
			|| (cmds[*i] == ' ' && cmds[*i + 1] != ' '))
		{
			(*i)--;
			return (0);
		}
		(*i)++;
	}
	(*i)--;
	return (1);
}

int	get_type_rdr(char *command, int i)
{
	if (command[i] == '>' && command[i + 1] == '>')
		return (2);
	else if (command[i] == '>')
		return (1);
	else if (command[i] == '<')
		return (0);
	return (-1);
}
