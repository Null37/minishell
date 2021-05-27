/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mor_fun_ac.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:58:59 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/27 12:58:43 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	len_many(int lenarg, t_commands *tmp, int i)
{
	if (lenarg > 1)
	{
		if (check_number(tmp, i) == 0)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			g_all->staus_code = 1;
		}
		else
			return (-1);
	}
	return (0);
}

void	err_number(t_commands *tmp)
{
	write(2, "minishell: ", 11);
	write(2, "exit: ", 6);
	write(2, tmp->arguments[0], strlen(tmp->arguments[0]));
	write(2, ": ", 2);
	write(2, "numeric argument required\n", 26);
}

void	free_all(void)
{
	if (g_all->old_pwd)
	{
		free(g_all->old_pwd);
		g_all->old_pwd = NULL;
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

int 	loop_add_env(t_norm norm, char **envp, char *s)
{
	while (++norm.i < norm.lenp)
	{
		norm.nameenv = get_env_name(envp[norm.i]);
		if (my_strcmp(norm.nameenv, norm.varibale) == 0)
		{
			norm.varibale = ft_strjoin1(norm.varibale, "=");
			s = envp[norm.i];
			envp[norm.i] = ft_strjoin1(norm.varibale, norm.te);
			free(s);
			free(norm.nameenv);
			return (-100);
		}
		free(norm.nameenv);
	}
	return (0);
}
