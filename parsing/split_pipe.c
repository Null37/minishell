/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:39:35 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/20 12:38:55 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	checkdbl_sngl_c(t_commands *commands, char *cmd, int *i)
{
	if ((cmd[++(*i)] == 34 && (*i) == 0))
	{
		commands->multiple = skip_double_coats(cmd, &(*i));
		if (commands->multiple)
			return (0);
	}
	else if ((cmd[(*i)] == 39 && (*i) == 0))
	{
		commands->multiple = skip_single_coats(cmd, &(*i));
		if (commands->multiple)
			return (0);
	}
	return (1);
}

int	norm_pipe(t_norm *n, t_commands **commands, int i)
{
	if (n->cmd[i] == 124)
	{
		n->cmd_tmp = (*commands)->command;
		(*commands)->command = my_substr(n->cmd, n->start, i);
		free(n->cmd_tmp);
		(*commands)->command = deletespace((*commands)->command);
		trait_command(n->envp, *commands);
		(*commands)->next_p = new_commands();
		*commands = (*commands)->next_p;
		n->start = i + 1;
	}
	else if (n->cmd[i] == '\0')
	{
		if (n->start == i)
			return (1);
		n->cmd_tmp = (*commands)->command;
		(*commands)->command = my_substr(n->cmd, n->start, i);
		free(n->cmd_tmp);
		(*commands)->command = deletespace((*commands)->command);
		trait_command(n->envp, *commands);
		return (1);
	}
	return (0);
}

t_norm	*new_norm2(char **envp, t_commands *commands)
{
	t_norm	*n;

	n = malloc(sizeof(t_norm));
	n->start = 0;
	n->tmp = commands;
	n->envp = envp;
	n->cmd = ft_strdup(commands->command);
	return (n);
}

int	split_pipe(char **envp, t_commands *commands)
{
	t_norm	*n;
	int		i;

	if (commands->command == NULL)
		return (0);
	i = -1;
	n = new_norm2(envp, commands);
	while (1)
	{
		if (!checkdbl_sngl_c(commands, n->cmd, &i))
		{
			free(n);
			return (0);
		}
		else if (n->cmd[i] == '\\')
		{
			i++;
			continue ;
		}
		if (norm_pipe(n, &commands, i))
			break ;
	}
	commands = n->tmp;
	free(n);
	return (1);
}
