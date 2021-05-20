/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:51:19 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/20 15:17:34 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

void	trait_command(char **envp, t_commands *commands)
{
	int	i;
	int	nbr_args;

	i = -1;
	nbr_args = 0;
	split_command_rdr(envp, commands, nbr_args);
	files_rdr(commands);
}

t_commands	*parssing_shell(char *ptr, t_env *evp, char *cmds)
{
	char		*buf;
	t_commands	*commands;
	t_commands	*tmp;

	buf = NULL;
	commands = new_commands();
	ptr = getcwd(buf, 1024);
	evp->ptr = ptr;
	get_commands(ptr, evp, commands, cmds);
	free(buf);
	free(ptr);
	return (commands);
}
