/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:51:19 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/22 11:52:04 by fbouibao         ###   ########.fr       */
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

void free_ags(t_commands *commands)
{
	int	i;

	i = -1;
	while (commands->arguments[++i])
	{
		free(commands->arguments[i]);
	}
	free(commands->arguments);
	free(commands->all);
}

void	free_files_rder(t_commands *commands)
{
	t_filerdr	*tmp;

	while (1)
	{
		if (commands->filerdr)
			tmp = commands->filerdr->next;
		else
			break ;
		free(commands->filerdr);
		commands->filerdr = tmp;
	}
}

void	free_node(t_commands *commands)
{
	t_commands	*tmp;

	while (1)
	{
		if (commands)
			tmp = commands->next_p;
		else
			break ;
		free(commands->path);
		free(commands->type);
		free(commands->command);
		free_ags(commands);
		free_files_rder(commands);
		free(commands);
		commands = tmp;
	}

}

void	free_list(t_commands *commands)
{
	t_commands	*tmp;

	
	while (1)
	{
		if (commands)
			tmp = commands->next;
		else
			break ;
		free_node(commands);
		commands = tmp;
	}
}
void	parssing_shell(char *ptr, t_env *evp, char *cmds)
{
	char		*buf;
	t_commands	*commands;
	t_commands	*tmp;

	buf = NULL;
	commands = new_commands();
	ptr = getcwd(buf, 1024);
	evp->ptr = ptr;
	get_commands(ptr, evp, &commands, cmds);
	free(buf);
	free(ptr);
	free_list(commands);
}
