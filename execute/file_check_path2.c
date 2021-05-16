/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_path2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:47:01 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/16 17:49:52 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	err_this_command(t_commands *tmp)
{
	write(2, "minishell: ", 11);
	write(2, tmp->type, ft_strlen(tmp->type));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	g_all->staus_code = 127;
}

int	half_check_w(t_commands *tmp, t_norm norm)
{
	if (ft_strncmp(tmp->type, "/", 1) != 0)
	{
		norm.com_path[norm.i] = ft_strjoin1(norm.com_path[norm.i], "/");
		norm.com_path[norm.i] = ft_strjoin1(norm.com_path[norm.i], tmp->type);
		norm.fs = check_if_command_is_exist(norm.com_path[norm.i], 1);
	}
	else if (ft_strncmp(tmp->type, "/", 1) == 0)
	{
		norm.ck = half_check_c_2(tmp, norm);
		if (norm.ck == 2)
			return (2);
		else if (norm.ck == -1)
			return (-1);
	}
	if (norm.fs == 0)
	{
		tmp->path = ft_strdup(norm.com_path[norm.i]);
		free_cmds(norm.com_path);
		free(norm.path);
		return (2);
	}
	else if (norm.fs == -1 && norm.i == norm.o - 1)
		err_this_command(tmp);
	return (0);
}

int	check_this_command(t_commands *tmp, t_env *evp)
{
	t_norm	norm;

	if (tmp->type == NULL)
		return (-1);
	norm.path = search_in_env2("PATH", evp->my_env);
	norm.ck = half_check_commad(tmp, norm.path);
	if (norm.ck == 2)
		return (2);
	else if (norm.ck == -1)
		return (-1);
	norm.com_path = ft_split(norm.path, ':');
	norm.o = len_of_args(norm.com_path);
	norm.i = -1;
	while (++norm.i != norm.o)
	{
		norm.ck = half_check_w(tmp, norm);
		if (norm.ck == 2)
			return (2);
		else if (norm.ck == -1)
			return (-1);
	}
	free_cmds(norm.com_path);
	free(norm.path);
	return (0);
}
