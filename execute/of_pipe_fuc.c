/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   of_pipe_fuc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:48:59 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/17 15:52:54 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	half_rid_zerot_commands(t_filerdr *lastnamef, t_norm *norm)
{
	norm->file = open(lastnamef->name, O_RDONLY);
	dup2(norm->file, 0);
	dup2(norm->write_fd, 1);
	close(norm->file);
}

void	half_pip_rid_one(t_norm *norm, t_filerdr *lastnamef)
{
	norm->file = open(lastnamef->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(norm->file, 1);
	dup2(norm->read_fd, 0);
	close(norm->file);
}

void	normal_pipe(t_norm	*norm)
{
	dup2(norm->read_fd, 0);
	dup2(norm->write_fd, 1);
	close(norm->read_fd);
	close(norm->write_fd);
	close(norm->fd_pipe[0]);
	close(norm->fd_pipe[1]);
}

void	reset(t_norm *norm, char *ptr)
{
	norm->read_fd = dup(0);
	norm->fd_input = -1;
	norm->fd_out = -2;
	norm->file = -50;
	norm->ptr2 = ptr;
}

void	parent(t_norm *norm, t_commands *tmp)
{
	close(norm->read_fd);
	close(norm->write_fd);
	if (tmp->next_p)
	{
		norm->read_fd = dup(norm->fd_pipe[0]);
		close(norm->fd_pipe[0]);
	}
}