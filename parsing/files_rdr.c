/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_rdr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:35:07 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/21 17:59:05 by rel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	norm_f_rdr(t_commands *commands, t_rdr *t_cmd, int *i)
{
	if (commands->command[*i] == 34)
		skip_double_coats(commands->command, i);
	else if (commands->command[*i] == 39)
		skip_single_coats(commands->command, i);
	else if (commands->command[*i] == '>' || commands->command[*i] == '<')
	{
		if (!commands->filerdr)
		{
			commands->filerdr = new_files_rdr();
			t_cmd->tmp = commands->filerdr;
		}
		else
		{
			commands->filerdr->next = new_files_rdr();
			commands->filerdr = commands->filerdr->next;
		}
		commands->filerdr->type = get_type_rdr(commands->command, *i);
		commands->filerdr->name = get_rdr_file(commands->command, *i);
		skip_filename(commands->command, i);
	}
}

int	files_rdr(t_commands *commands)
{
	int		i;
	t_rdr	*t_cmd;

	i = -1;
	t_cmd = malloc(sizeof(t_rdr));
	t_cmd->tmp = NULL;
	while (commands->command[++i])
		norm_f_rdr(commands, t_cmd, &i);
	commands->filerdr = t_cmd->tmp;
	free(t_cmd);
	return (0);
}
