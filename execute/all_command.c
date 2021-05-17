/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 12:36:37 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/17 15:45:09 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	our_command(t_commands *tmp, char *ptr, t_env *evp)
{
	char	*test;

	test = search_in_env2("PWD", evp->my_env);
	if (ft_strncmp(test, "", 1) != 0)
		g_all->old_pwd = search_in_env2("PWD", evp->my_env);
	free(test);
	if (tmp->type == NULL && !tmp->next)
		return (0);
	if (ft_strncmp(tmp->type, "cd", 3) == 0)
		command_cd(ptr, tmp, evp);
	else if (ft_strncmp(tmp->type, "pwd", 4) == 0)
		command_pwd(ptr, evp);
	else if (ft_strncmp(tmp->type, "exit", 5) == 0)
		command_exit(tmp, 0);
	else if (ft_strncmp(tmp->type, "env", 4) == 0)
		command_env(evp->my_env);
	else if (ft_strncmp(tmp->type, "export", 7) == 0)
		command_export(tmp, evp);
	else if (ft_strncmp(tmp->type, "unset", 6) == 0)
		command_unset(tmp, evp);
	else if (ft_strncmp(tmp->type, "echo", 6) == 0)
		command_echo(tmp);
	else
		command_in_the_sys(tmp, evp->my_env);
	return (0);
}

void	se_execute_command(t_commands *tmp, char *ptr, t_env *evp)
{
	char	*test;

	test = search_in_env2("PWD", evp->my_env);
	if (ft_strncmp(test, "", 1) != 0)
		g_all->old_pwd = search_in_env2("PWD", evp->my_env);
	free(test);
	if (ft_strncmp(tmp->type, "cd", 3) == 0)
		command_cd(ptr, tmp, evp);
	else if (ft_strncmp(tmp->type, "pwd", 4) == 0)
		command_pwd(ptr, evp);
	else if (ft_strncmp(tmp->type, "exit", 5) == 0)
		command_exit(tmp, 1);
	else if (ft_strncmp(tmp->type, "env", 4) == 0)
		command_env(evp->my_env);
	else if (ft_strncmp(tmp->type, "export", 7) == 0)
		command_export(tmp, evp);
	else if (ft_strncmp(tmp->type, "unset", 6) == 0)
		command_unset(tmp, evp);
	else if (ft_strncmp(tmp->type, "echo", 6) == 0)
		command_echo(tmp);
	else
	{
		check_this_command(tmp, evp, 1);
		if(g_all->pipe_err == 1)
		{
			err_this_command(tmp, 0);
			return ;
		}
		if (execve(tmp->path, tmp->all, evp->my_env) < 0)
			error_execve(tmp);
	}
}

void	half_exit(t_commands *tmp, int i)
{
	while (tmp->arguments[0][i])
	{
		if (ft_isdigit2(tmp->arguments[0][i]) == 1)
			i++;
		else
		{
			write(2, "minishell: ", 11);
			write(2, "exit: ", 6);
			write(2, tmp->arguments[0], strlen(tmp->arguments[0]));
			write(2, ": ", 2);
			write(2, "numeric argument required\n", 26);
			free(tmp->arguments[0]);
			tmp->arguments[0] = NULL;
			exit(-1);
		}
	}
}

void	command_exit(t_commands *tmp, int pipe)
{
	int	lenarg;
	int	ex;
	int	i;

	i = 0;
	if (pipe == 0)
		write(2, "exit\n", 5);
	lenarg = len_of_args(tmp->arguments);
	if (tmp->arguments[0] != NULL)
		half_exit(tmp, i);
	if (lenarg == 1 || lenarg == 0)
	{
		if (lenarg == 0)
			ex = 0;
		else
			ex = ft_atoi(tmp->arguments[0]);
		free(tmp->arguments[0]);
		tmp->arguments[0] = NULL;
		exit(ex);
	}
	else if (lenarg > 1)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_all->staus_code = 1;
	}
}

void	error_execve(t_commands *tmp)
{
	char	*error;

	error = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, tmp->type, ft_strlen(tmp->type));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	g_all->staus_code = 127;
}
