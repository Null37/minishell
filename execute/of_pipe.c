/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   of_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:56:57 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/27 12:50:29 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	rid_with_pipe(t_commands *tmp, t_filerdr *lastnamef,
	t_norm *norm)
{
	pip_rid_one(tmp, lastnamef, norm);
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
		rid_with_pipe(tmp, lastnamef, norm);
	se_execute_command(tmp, norm->ptr2, evp);
	if (tmp->type == NULL)
		exit(0);
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
	lastnamef = NULL;
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
