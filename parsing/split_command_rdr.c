/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_rdr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:33:46 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/27 15:05:32 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

t_rdr	*newcmd_rdr(void)
{
	t_rdr	*r;

	r = malloc(sizeof(t_rdr));
	r->b = 0;
	r->k = 0;
	r->i = -1;
	r->start = 0;
	return (r);
}

void	nrm_rdr_args(t_rdr	*cmd_r, char **envp, t_commands *commands)
{
	cmd_r->str = my_substr(cmd_r->rdr_cmd, cmd_r->start, cmd_r->i + 1);
	cmd_r->str = deletespace(cmd_r->str);
	cmd_r->str = deletecoats(envp, cmd_r->str);
	if (cmd_r->str)
	{
		if (cmd_r->b == 1 || my_strcmp(commands->type, "echo") == 1
			|| (my_strcmp(commands->type, "echo") == 0
				&& check_echo_n(cmd_r->str) == 1))
		{
			commands->arguments[cmd_r->k] = cmd_r->str;
			cmd_r->k++;
			commands->all[cmd_r->k] = commands->arguments[cmd_r->k - 1];
			cmd_r->b = 1;
		}
		else if (cmd_r->b == 0)
			commands->option = 1;
	}
}

int	skp_sng_db_c_n(t_rdr *cmd_r)
{
	if ((cmd_r->rdr_cmd[++(cmd_r->i)] == 34 && cmd_r->i == 0)
		|| (cmd_r->rdr_cmd[cmd_r->i] == 34
			&& cmd_r->rdr_cmd[cmd_r->i - 1] != '\\'))
	{
		skip_double_coats(cmd_r->rdr_cmd, &cmd_r->i);
		return (1);
	}
	else if ((cmd_r->rdr_cmd[cmd_r->i] == 39 && cmd_r->i == 0)
		|| (cmd_r->rdr_cmd[cmd_r->i] == 39
			&& cmd_r->rdr_cmd[cmd_r->i - 1] != '\\'))
	{
		skip_single_coats(cmd_r->rdr_cmd, &cmd_r->i);
		return (1);
	}
	return (0);
}

int	rdr_norm_cmd(t_rdr *cm_r, char **envp, t_commands *commands)
{
	if (cm_r->rdr_cmd && !skp_sng_db_c_n(cm_r) && cm_r->rdr_cmd[cm_r->i] == '\\')
	{
		(cm_r->i)++;
		return (1);
	}
	if ((cm_r->rdr_cmd[cm_r->i] == ' ' && cm_r->rdr_cmd[cm_r->i + 1] != ' ')
		|| cm_r->rdr_cmd[cm_r->i] == '\0')
	{
		if (!commands->type)
		{
			commands->type = my_substr(cm_r->rdr_cmd, cm_r->start, cm_r->i + 1);
			commands->type = deletespace(commands->type);
			commands->type = deletecoats(envp, commands->type);
			if (!commands->type)
				commands->type = ft_strdup("\0");
			commands->all[0] = commands->type;
		}
		else
			nrm_rdr_args(cm_r, envp, commands);
		cm_r->start = cm_r->i + 1;
	}
	if (cm_r->rdr_cmd[cm_r->i] == '\0')
		return (2);
	return (0);
}

void	split_command_rdr(char **envp, t_commands *commands, int nbr_args)
{
	t_rdr	*cmd_r;
	int		t;

	cmd_r = newcmd_rdr();
	cmd_r->rdr_cmd = deleterdr(commands->command);
	cmd_r->rdr_cmd = deletespace(cmd_r->rdr_cmd);
	if (!cmd_r->rdr_cmd || ft_strlen(cmd_r->rdr_cmd) == 0)
		return ;
	nbr_args = nbr_argts2(cmd_r->rdr_cmd);
	commands->arguments = malloc(sizeof(char *) * (nbr_args));
	commands->all = malloc(sizeof(char *) * (nbr_args + 1));
	add_null(commands, nbr_args + 1);
	while (1)
	{
		t = rdr_norm_cmd(cmd_r, envp, commands);
		if (t == 1)
			continue ;
		else if (t == 2)
			break ;
	}
	free(cmd_r->rdr_cmd);
	free(cmd_r);
}
