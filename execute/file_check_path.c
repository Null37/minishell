/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 15:24:10 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/17 15:39:42 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	free_cmds(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		free(cmd[i]);
	}
	free(cmd);
}

void	erro_h_chek_c(t_commands *tmp, int pipe)
{
	if	(pipe == 0)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->type, ft_strlen(tmp->type));
		write(2, ": ", 2);
		write(2, "command not found\n", 18);
	}
	g_all->pipe_err = 1;
	g_all->staus_code = 127;
}

int	built_check(t_commands *tmp)
{
	if (my_strcmp("exit", tmp->type) == 0 || my_strcmp("export", tmp->type) == 0
		|| my_strcmp("unset", tmp->type) == 0
		|| my_strcmp("cd", tmp->type) == 0
		|| my_strcmp("echo", tmp->type) == 0
		|| my_strcmp("pwd", tmp->type) == 0)
		return (2);
	return (0);
}

int	half_check_commad(t_commands *tmp, char *path, int pipe)
{
	if (built_check(tmp) == 2)
		return (2);
	if (tmp->type[0] == '\0')
	{
		erro_h_chek_c(tmp, pipe);
		return (-1);
	}
	if (ft_strncmp(path, "", 1) == 0)
	{
		if (check_if_command_is_exist(tmp->type, 1, pipe) != 3)
		{
			tmp->path = tmp->type;
			return (2);
		}
	}
	if (ft_strncmp(tmp->type, "./", 2) == 0
		|| ft_strncmp(tmp->type, "../", 3) == 0)
	{
		if (check_if_command_is_exist(tmp->type, 1, pipe) == 3)
			return (-1);
		tmp->path = tmp->type;
		return (2);
	}
	return (0);
}

int	half_check_c_2(t_commands *tmp, t_norm norm, int pipe)
{
	norm.fs = check_if_command_is_exist(tmp->type, 1, pipe);
	if (norm.fs == 0)
	{
		tmp->path = tmp->type;
		free_cmds(norm.com_path);
		free(norm.path);
		return (2);
	}
	else if (norm.fs == -1 && norm.i == norm.o - 1)
	{
		print_error_check_commd(tmp, pipe);
		free_cmds(norm.com_path);
		free(norm.path);
		return (-1);
	}
	return (0);
}
