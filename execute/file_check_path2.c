/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_path2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:47:01 by ssamadi           #+#    #+#             */
/*   Updated: 2021/06/05 16:14:06 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	err_this_command(t_commands *tmp, int pipe)
{
	if (pipe == 0)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->type, ft_strlen(tmp->type));
		write(2, ": ", 2);
		write(2, "command not found\n", 18);
	}
	g_all->pipe_err = 1;
	g_all->staus_code = 127;
}

int	half_check_w(t_commands *tmp, t_norm norm, int pipe)
{
	if (ft_strncmp(tmp->type, "/", 1) != 0)
	{
		norm.com_path[norm.i] = ft_strjoin1(norm.com_path[norm.i], "/");
		norm.com_path[norm.i] = ft_strjoin1(norm.com_path[norm.i], tmp->type);
		norm.fs = check_if_command_is_exist(norm.com_path[norm.i], 1, pipe);
	}
	else if (ft_strncmp(tmp->type, "/", 1) == 0)
	{
		norm.ck = half_check_c_2(tmp, norm, pipe);
		if (norm.ck == 2)
			return (2);
		else if (norm.ck == -1)
			return (-1);
	}
	if (norm.fs == 0)
	{
		tmp->path = ft_strdup(norm.com_path[norm.i]);
		return (2);
	}
	else if (norm.fs == -1 && norm.i == norm.o - 1)
		err_this_command(tmp, pipe);
	return (0);
}

int	loop_chk_command(t_norm	norm, t_commands *tmp, int pipe)
{
	while (++norm.i != norm.o)
	{
		norm.ck = half_check_w(tmp, norm, pipe);
		if (norm.ck == 2)
		{
			free_cmds(norm.com_path);
			return (2);
		}
		else if (norm.ck == -1)
		{
			free_cmds(norm.com_path);
			return (-1);
		}
	}
	return (0);
}

int	chek_fre(t_norm	norm)
{
	if (norm.ck == 2)
	{
		free(norm.path);
		return (2);
	}
	else if (norm.ck == -1)
	{
		free(norm.path);
		return (-1);
	}
	return (0);
}

int	check_this_command(t_commands *tmp, t_env *evp, int pipe)
{
	t_norm	norm;
	int		l;

	g_all->pipe_err = 0;
	if (err_half_command(tmp) == -1)
		return (-1);
	norm.path = search_in_env2("PATH", evp->my_env);
	norm.ck = half_check_commad(tmp, norm.path, pipe);
	l = chek_fre(norm);
	if (l == 2)
		return (2);
	else if (l == -1)
		return (-1);
	norm.com_path = ft_split(norm.path, ':');
	free(norm.path);
	norm.o = len_of_args(norm.com_path);
	norm.i = -1;
	norm.ck2 = loop_chk_command(norm, tmp, pipe);
	if (norm.ck2 == 2)
		return (2);
	else if (norm.ck2 == -1)
		return (-1);
	if (norm.com_path)
		free_cmds(norm.com_path);
	return (0);
}
