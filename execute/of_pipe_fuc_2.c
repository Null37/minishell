/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   of_pipe_fuc_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:56:55 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/20 14:57:01 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	pip_rid_one(t_commands *tmp, t_filerdr *lastnamef,
	t_env *evp, t_norm *norm)
{
	norm->pipe_ch = 1;
	if (check_two_red(tmp) == 0)
	{
		lastnamef = last_name_func(tmp);
		if (!lastnamef)
			exit(1);
		if (check_if_command_is_exist(tmp->filerdr->name, 0,
				norm->pipe_ch) == 3)
			exit(1);
		if (lastnamef->type == 0)
			half_rid_zerot_commands(lastnamef, norm);
		else if (lastnamef->type == 1)
			half_pip_rid_one(norm, lastnamef);
		else if (lastnamef->type == 2)
		{
			norm->file = open(lastnamef->name, O_CREAT | O_WRONLY | O_APPEND,
					0644);
			dup2(norm->file, 1);
			dup2(norm->read_fd, 0);
			close(norm->file);
		}
	}
}

void	start_pipe(t_norm *norm)
{
	pipe(norm->fd_pipe);
	norm->write_fd = dup(norm->fd_pipe[1]);
	close(norm->fd_pipe[1]);
}

int	half_else_exu(t_commands *tmp, t_env *evp)
{
	check_this_command(tmp, evp, 1);
	if (g_all->pipe_err == 1)
	{
		err_this_command(tmp, 0);
		return (-1);
	}
	if (execve(tmp->path, tmp->all, evp->my_env) < 0)
		error_execve(tmp);
	return (0);
}
