/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 15:24:10 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/12 17:38:17 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int check_this_command(t_commands *tmp,t_env *evp)
{
	char *path;

	if(tmp->type == NULL)
		return -1;
	char **command_path;
	int o;
	int fs;
	int i;
	int fd;
	char *erna;
	if (my_strcmp("exit", tmp->type) == 0 || my_strcmp("export", tmp->type) == 0
	|| my_strcmp("unset", tmp->type) == 0 || my_strcmp("cd", tmp->type) == 0 
	|| my_strcmp("echo", tmp->type) == 0 || my_strcmp("pwd", tmp->type) == 0)
		return 2;
	path = search_in_env2("PATH", evp->my_env);
	if(ft_strncmp(path, "", 1) == 0)
	{
		if(check_if_command_is_exist(tmp->type, 1) != 3) 
		{
			tmp->path = tmp->type;
			return 2;
		}
	}
	if(ft_strncmp(tmp->type, "./", 2) == 0 || ft_strncmp(tmp->type, "../", 3) == 0)
	{
		if(check_if_command_is_exist(tmp->type, 1) == 3)
			return 0;
		tmp->path = tmp->type;
		return 2;
	}
	command_path =  ft_split(path, ':');
	o = len_of_args(command_path);
	i = 0;
	//check_if_command_is_exist(tmp->type, 1);
	while(i != o)
	{
		if(ft_strncmp(tmp->type, "/", 1) != 0)
		{
			command_path[i] = ft_strjoin(command_path[i], "/");
			command_path[i] = ft_strjoin(command_path[i], tmp->type);
			fs = check_if_command_is_exist(command_path[i], 1);
		}
		else if(ft_strncmp(tmp->type, "/", 1) ==0)
		{
			fs = check_if_command_is_exist(tmp->type, 1);
			if(fs == 0)
			{
				tmp->path = tmp->type;
				return 2;
			}
			else if (fs == -1 &&  i == o - 1)
			{
				print_error_check_commd(tmp);
				return 0;
			}
		}
		if (fs == 0)
		{
			tmp->path = command_path[i];
			return 2;
		}
		else if (fs == -1 &&  i == o - 1)
		{
			write(2, "minishell: ", 11);
			write(2, tmp->type, ft_strlen(tmp->type));
			write(2,": ", 2);
			write(2, "command not found\n", 18);
			g_all->staus_code = 127;
		}
		i++;
	}
	return 0;
}