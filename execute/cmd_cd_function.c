/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:03:15 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/11 13:24:57 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	half_cd(char *ptr, t_env *evp, char *oldpwd)
{
	ptr = search_in_env2("PWD", evp->my_env);
	oldpwd = ft_strdup(ptr);
	ptr = ft_strjoin1(ptr, "/.");
	evp->my_env = edit_evp_new_oldpwd(oldpwd, evp->my_env);
	evp->my_env = edit_envp_pwd(ptr, evp->my_env);
	write(2, "cd: error retrieving current directory: getcwd: ", 48);
	write(2, "cannot access parent directories: ", 34);
	write(2, "No such file or directory\n", 26);
}

int	half_cd_2(t_commands *tmp, t_env *evp, char *home, int eee)
{
	if (tmp->arguments[0] == NULL)
	{
		home = search_in_env2("HOME", evp->my_env);
		eee = chdir(home);
		if (ft_strncmp(home, "", 1) == 0)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (-9);
		}
	}
	else if (ft_strncmp(tmp->arguments[0], "~", 2) == 0)
	{
		home = search_in_env2("HOME", evp->my_env);
		if (ft_strncmp(home, "", 1) == 0)
			chdir(evp->save);
		else
			eee = chdir(home);
	}
	else
		eee = chdir(tmp->arguments[0]);
	return (eee);
}

void	command_cd(char *ptr, t_commands *tmp, t_env *evp)
{
	int		eee;
	char	*home;
	char	*oldpwd;
	char	*ee;

	if (ptr != NULL)
		evp->my_env = edit_evp_new_oldpwd(ptr, evp->my_env);
	if (ptr == NULL && ft_strncmp(tmp->arguments[0], ".", 2) == 0)
		half_cd(ptr, evp, oldpwd);
	eee = half_cd_2(tmp, evp, home, eee);
	if (eee == -9)
		return ;
	if (eee == -1)
	{
		write(2, "Minishell: ", 11);
		write(2, "cd: ", 4);
		if (tmp->arguments[0] != NULL)
			write(2, tmp->arguments[0], ft_strlen(tmp->arguments[0]));
		else
			write(2, home, ft_strlen(home));
		write(2, ": ", 2);
		ee = strerror(errno);
		write(2, ee, strlen(ee));
		write(2, "\n", 1);
	}
}
