/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:51:19 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/25 20:44:18 by rel-bour         ###   ########.fr       */
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
	if(commands->arguments == NULL)
		return ;		
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
		free(commands->filerdr->name);
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

char	*convert_vrbs(char *cmds, t_env *evp)
{
	t_tmp	*tmp;
	int		bl;

	bl = 0;
	tmp = malloc(sizeof(t_tmp));
	tmp->rstr = ft_strdup("");
	tmp->i = -1;
	while (cmds[++tmp->i])
	{
		if (bl == 0 && cmds[tmp->i] == '\'' && (tmp->i == 0 || cmds[tmp->i - 1] != '\\'))
			bl = 1;
		else if (bl == 1 && cmds[tmp->i] == '\'')
			bl = 0;	
		if (bl == 0 && cmds[tmp->i] == '\\' && cmds[tmp->i + 1] == '$')
		{
			tmp->rstr = ft_strjoinchar(tmp->rstr, '\\');
			tmp->rstr = ft_strjoinchar(tmp->rstr, '$');
			tmp->i++;
			continue ;
		}
		if (bl == 0 && cmds[tmp->i] == '$' && cmds[tmp->i + 1] == '?')
		{
			tmp->ss = ft_itoa(g_all->staus_code);
			tmp->rstr = ft_strjoin1(tmp->rstr, tmp->ss);
			free(tmp->ss);
			tmp->i++;
		}
		else if (bl == 0 && cmds[tmp->i] == '$')
		{
			tmp->rstr = add_vrbs(evp->my_env, tmp->rstr, tmp, cmds);
		}
		else
		{
			tmp->rstr = ft_strjoinchar(tmp->rstr, cmds[tmp->i]);
		}
		
	}
	cmds = tmp->rstr;
	free(tmp);
	return (cmds);
}

void	parssing_shell(char *ptr, t_env *evp, char *cmds)
{
	char		*buf;
	t_commands	*commands;
	t_commands	*tmp;

	buf = NULL;
	cmds = convert_vrbs(cmds,evp);
	commands = new_commands();
	ptr = getcwd(buf, 1024);
	evp->ptr = ptr;
	get_commands(ptr, evp, &commands, cmds);
	free(buf);
	free(ptr);
	free(cmds);
	free_list(commands);
}
