/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_func_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:16:25 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/25 11:30:43 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	my_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (1);
	while (1)
	{
		if (s1[++i] != s2[++j])
			return (1);
		if (s1[i] == '\0' || s2[j] == '\0')
			break ;
	}
	return (0);
}

int	check_file_or_dit(char *path_file)
{
	DIR				*dir;
	struct dirent	*dp;

	dir = opendir(path_file);
	if (dir != NULL)
	{
		write(2, "minishell: ", 11);
		write(2, path_file, ft_strlen(path_file));
		write(2, ": ", 2);
		write(2, "is a directory\n", 15);
		g_all->staus_code = 126;
		return (3);
	}
	return (0);
}

int	check_permissions(char *path_file, struct stat stats, int exute)
{
	if ((stats.st_mode & R_OK) && (stats.st_mode & W_OK) && exute == 0)
		return (1);
	else if ((stats.st_mode & X_OK) && exute == 1)
		return (2);
	else if ((!(stats.st_mode & R_OK) && !(stats.st_mode & X_OK))
		|| (!(stats.st_mode & X_OK) && exute == 1))
	{
		write(2, "minishell: ", 11);
		write(2, path_file, ft_strlen(path_file));
		write(2, ": ", 2);
		write(2, "Permission denied\n", 18);
		g_all->staus_code = 126;
		return (1);
	}
	return (0);
}
