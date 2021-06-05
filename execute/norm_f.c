/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:13:45 by fbouibao          #+#    #+#             */
/*   Updated: 2021/06/05 16:15:45 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	err_half_command(t_commands *tmp)
{
	if (tmp->type == NULL)
		return (-1);
	if (err_handling(tmp) == -1)
		return (-1);
	return (0);
}

int	err_handling(t_commands *tmp)
{
	if (ft_strncmp(tmp->type, ".", 2) == 0)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->type, 1);
		write(2, ": ", 2);
		write(2, "filename argument required\n", 27);
		write(2, tmp->type, 1);
		write(2, ": ", 2);
		write(2, "usage: . filename [arguments]\n", 30);
		g_all->staus_code = 2;
		return (-1);
	}
	if (ft_strncmp(tmp->type, "..", 3) == 0)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->type, 2);
		write(2, ": ", 2);
		write(2, "command not found\n", 18);
		g_all->staus_code = 127;
		return (-1);
	}
	return (0);
}
