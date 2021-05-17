/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   of_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:56:57 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/17 15:55:18 by ssamadi          ###   ########.fr       */
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

void	rid_with_pipe(t_commands *tmp, t_filerdr *lastnamef,
	t_env *evp, t_norm *norm)
{
	pip_rid_one(tmp, lastnamef, evp, norm);
	if (check_two_red(tmp) == 1)
	{
		norm->fd_out = output_ret(tmp);
		if (norm->fd_out == -100)
			exit(1);
		norm->fd_input = input_ret(tmp);
		if (norm->fd_input == -100)
			exit(1);
		dup2(norm->fd_input, 0);
		close(norm->fd_input);
		dup2(norm->fd_out, 1);
		close(norm->fd_out);
	}
}

void	all_work_p_r(t_commands *tmp, t_filerdr *lastnamef,
	t_env *evp, t_norm *norm)
{
	if (tmp != NULL && tmp->filerdr == NULL)
		normal_pipe(norm);
	else if (tmp->filerdr != NULL)
		rid_with_pipe(tmp, lastnamef, evp, norm);
	se_execute_command(tmp, norm->ptr2, evp);
	exit(127);
}

void	start_loop(t_commands *tmp, t_filerdr *lastnamef,
	t_env *evp, t_norm *norm)
{
	while (tmp)
	{
		norm->fd_pipe[0] = -1;
		norm->fd_pipe[1] = -1;
		if (tmp->next_p)
			start_pipe(norm);
		else
			norm->write_fd = dup(1);
		g_all->ctrl_quit = 1;
		if (fork() == 0)
			all_work_p_r(tmp, lastnamef, evp, norm);
		else
			parent(norm, tmp);
		tmp = tmp->next_p;
	}
}

void	pipe_commmand_c(t_commands *tmp, char *ptr, t_env *evp)
{
	t_filerdr	*lastnamef;
	t_norm		*norm;
	int			i;

	i = 0;
	norm = malloc(sizeof(t_norm));
	reset(norm, ptr);
	start_loop(tmp, lastnamef, evp, norm);
	while (wait(&g_all->staus_code) > 0)
		i++;
	if (WIFSIGNALED(g_all->staus_code))
        g_all->staus_code = WTERMSIG(g_all->staus_code) + 128;
    else
        g_all->staus_code = WEXITSTATUS(g_all->staus_code) % 128;
	free(norm);
}
