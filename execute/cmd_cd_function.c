/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:03:15 by ssamadi           #+#    #+#             */
/*   Updated: 2021/06/11 11:47:23 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	half_cd(char *ptr, t_env *evp, char *oldpwd)
{
	oldpwd = ft_strdup(ptr);
	if (ptr == NULL)
	{
		ptr = search_in_env2("PWD", evp->my_env);
		ptr = ft_strjoin1(ptr, "/.");
		evp->my_env = edit_evp_new_oldpwd(oldpwd, evp->my_env);
		evp->my_env = edit_envp_pwd(ptr, evp->my_env);
	}
	else
		g_all->old_pwd = ft_strjoin1(g_all->old_pwd, "/.");
	write(2, "cd: error retrieving current directory: getcwd: ", 48);
	write(2, "cannot access parent directories: ", 34);
	write(2, "No such file or directory\n", 26);
	free(ptr);
	free(oldpwd);
}

int	half_cd_2(t_commands *tmp, t_env *evp, char *home, int eee)
{
	if (tmp->arguments[0] == NULL)
	{
		home = search_in_env2("HOME", evp->my_env);
		eee = chdir(home);
		if (home == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			free(home);
			g_all->staus_code = 1;
			return (-9);
		}
		free(home);
	}
	else if (ft_strncmp(tmp->arguments[0], "~", 2) == 0)
	{
		home = search_in_env2("HOME", evp->my_env);
		if (home == NULL)
			chdir(evp->save);
		else
			eee = chdir(home);
		free(home);
	}
	else
		eee = chdir(tmp->arguments[0]);
	return (eee);
}

void	erro_cd(char *home, t_commands *tmp)
{
	char	*ee;

	write(2, "Minishell: ", 11);
	write(2, "cd: ", 4);
	if (tmp->arguments[0] != NULL)
		write(2, tmp->arguments[0], ft_strlen(tmp->arguments[0]));
	else
		write(2, home, ft_strlen(home));
	write(2, ": ", 2);
	ee = strerror(errno);
	write(2, ee, ft_strlen(ee));
	write(2, "\n", 1);
	g_all->staus_code = 1;
}

void	command_cd(char *ptr, t_commands *tmp, t_env *evp)
{
	int		eee;
	char	*home;
	char	*oldpwd;

	home = NULL;
	oldpwd = NULL;
	eee = 0;
	if (ptr != NULL)
		evp->my_env = edit_evp_new_oldpwd(ptr, evp->my_env);
	if (ptr == NULL && ft_strncmp(tmp->arguments[0], ".", 2) == 0)
		half_cd(ptr, evp, oldpwd);
	eee = half_cd_2(tmp, evp, home, eee);
	if (eee == -9)
		return ;
	if (eee == -1)
		erro_cd(home, tmp);
	else
		g_all->staus_code = 0;
}
