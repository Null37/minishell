/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_cnt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:24:13 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/20 15:21:02 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	norm_smpl_cpd(char *cmds, t_env *evp, t_commands *commands, int i)
{
	evp->ptr = getcwd(evp->buf, 1024);
	commands->command = my_substr(cmds, evp->start, i);
	commands->command = deletespace(commands->command);
	split_pipe(evp->my_env, commands);
	if (commands->next_p == NULL)
	{
		if (commands->filerdr == NULL)
		{
			if (check_this_command(commands, evp, 1) == 2)
				our_command(commands, evp->ptr, evp);
		}
		else if (commands->filerdr != NULL)
			mini_redrection(commands, evp->ptr, evp);
		free(evp->buf);
		free(evp->ptr);
		return (1);
	}
	free(evp->buf);
	free(evp->ptr);
	return (0);
}

t_commands	*norm_commands1(char *cmds, t_env *evp, t_commands *commands, int i)
{
	if (!norm_smpl_cpd(cmds, evp, commands, i) && commands->next_p != NULL)
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
	commands->next = new_commands();
	commands = commands->next;
	evp->start = i + 1;
	return (commands);
}
