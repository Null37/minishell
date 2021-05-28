/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   of_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:53:52 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/28 13:46:17 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	half_in_ou(t_commands *tmp,
	t_norm norm, t_env *evp, t_filerdr *lastnamef)
{
	if (lastnamef->type == 0)
	{
		norm.fd_in = open(lastnamef->name, O_RDONLY);
		norm.saved_input = dup(0);
		close(0);
		dup2(norm.fd_in, 0);
		if (check_this_command(tmp, evp, norm.pipe_ch) == 2)
			our_command(tmp, norm.ptr2, evp);
		dup2(norm.saved_input, 0);
		close(norm.saved_input);
		close(norm.fd_in);
	}
	else if (lastnamef->type == 1)
	{
		norm.fd_o = open(lastnamef->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		norm.saved_stdout = dup(1);
		close(1);
		dup2(norm.fd_o, 1);
		if (check_this_command(tmp, evp, norm.pipe_ch) == 2)
			our_command(tmp, norm.ptr2, evp);
		dup2(norm.saved_stdout, STDOUT_FILENO);
		close(norm.saved_stdout);
		close(norm.fd_o);
	}
}

void	half_ou_two(t_commands *tmp,
	t_norm norm, t_env *evp, t_filerdr *lastnamef)
{
	if (lastnamef->type == 2)
	{
		norm.fd_o = open(lastnamef->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		norm.saved_stdout = dup(1);
		close(1);
		dup2(norm.fd_o, 1);
		if (check_this_command(tmp, evp, norm.pipe_ch) == 2)
			our_command(tmp, norm.ptr2, evp);
		dup2(norm.saved_stdout, STDOUT_FILENO);
		close(norm.saved_stdout);
		close(norm.fd_o);
	}
}

int	half_in(t_commands *tmp, t_norm norm, t_env *evp, int pipe)
{
	g_all->yesdup = 1;
	g_all->redir_fd = output_ret(tmp);
	if (g_all->redir_fd == -100)
		return (-1);
	g_all->redir_fd_in = input_ret(tmp);
	if (g_all->redir_fd_in == -100)
		return (-1);
	if (check_this_command(tmp, evp, pipe) == 2)
		our_command(tmp, norm.ptr2, evp);
	g_all->yesdup = 0;
	return (0);
}

void	reset_red(t_norm norm)
{
	g_all->redir_fd = -100;
	g_all->redir_fd_in = -100;
	norm.fd_o = -200;
	norm.fd_in = -100;
}

void	mini_redrection(t_commands *tmp, char *ptr, t_env *evp)
{
	t_filerdr	*t;
	t_norm		norm;
	t_filerdr	*lastnamef;

	norm.pipe_ch = 0;
	reset_red(norm);
	t = tmp->filerdr;
	norm.ptr2 = ptr;
	if (check_two_red(tmp) == 0)
	{
		lastnamef = last_name_func(tmp);
		if (!lastnamef)
			return ;
		if (check_if_command_is_exist(tmp->filerdr->name, 0, norm.pipe_ch) == 3)
		{
			g_all->staus_code = 1;
			free(lastnamef);
			return ;
		}
		half_in_ou(tmp, norm, evp, lastnamef);
		half_ou_two(tmp, norm, evp, lastnamef);
	}
	else if (check_two_red(tmp) == 1)
		if (half_in(tmp, norm, evp, norm.pipe_ch) == -1)
			return ;
}
