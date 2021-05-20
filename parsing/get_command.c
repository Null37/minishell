/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:13:43 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/20 15:22:15 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	ext_cmd_norm(t_env *evp, t_commands *commands)
{
	if (commands->filerdr == NULL)
	{
		if (check_this_command(commands, evp, 0) == 2)
			our_command(commands, evp->ptr, evp);
	}
	else if (commands->filerdr != NULL)
		mini_redrection(commands, evp->ptr, evp);
}

t_commands	*norm_commands2(char *cmds, t_env *evp, t_commands *commands, int i)
{
	evp->ptr = getcwd(evp->buf, 1024);
	commands->command = my_substr(cmds, evp->start, i);
	commands->command = deletespace(commands->command);
	split_pipe(evp->my_env, commands);
	if (commands->next_p == NULL)
		ext_cmd_norm(evp, commands);
	else if (commands->next_p != NULL)
	{
		evp->tpp = commands;
		while (1)
		{
			check_this_command(commands, evp, 1);
			if (!commands->next_p)
				break ;
			commands = commands->next_p;
		}
		commands = evp->tpp;
		pipe_commmand_c(commands, evp->ptr, evp);
	}
	free(evp->buf);
	free(evp->ptr);
	return (commands);
}

int	norm_g_cmd0(int *i, t_commands *commands, char *cmds)
{
	if ((cmds[++(*i)] == 34 && *i == 0)
		|| (cmds[*i] == 34 && cmds[*i - 1] != '\\'))
	{
		commands->multiple = skip_double_coats(cmds, i);
		if (commands->multiple)
			return (0);
	}
	else if ((cmds[*i] == 39 && *i == 0)
		|| (cmds[*i] == 39 && cmds[*i - 1] != '\\'))
	{
		commands->multiple = skip_single_coats(cmds, i);
		if (commands->multiple)
			return (0);
	}
	return (1);
}

int	norm_g_cmd1(int *i, t_env *evp, t_commands **commands, char *cmds)
{
	if (cmds[*i] == 59)
		*commands = norm_commands1(cmds, evp, *commands, *i);
	else if (cmds[*i] == '\0')
	{
		if (evp->start == *i)
			return (1);
		*commands = norm_commands2(cmds, evp, *commands, *i);
		return (1);
	}
	return (0);
}

int	get_commands(char *ptr, t_env *evp, t_commands *cmm, char *cmds)
{
	int			i;
	t_commands	*tmp;

	evp->buf = NULL;
	i = -1;
	evp->start = 0;
	tmp = cmm;
	while (1)
	{
		if (!norm_g_cmd0(&i, cmm, cmds))
			return (0);
		else if (cmds[i] == '\\')
		{
			i++;
			continue ;
		}
		if (norm_g_cmd1(&i, evp, &cmm, cmds))
			break ;
	}
	cmm = tmp;
	return (1);
}
