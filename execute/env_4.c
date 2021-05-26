/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:10:22 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/26 18:19:39 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	error_syntax(t_commands *tmp, int k)
{
	write(2, "minishell: ", 11);
	write(2, "export: ", 7);
	write(2, "`", 1);
	write(2, tmp->arguments[k], strlen(tmp->arguments[k]));
	write(2, "'", 1);
	write(2, ": ", 2);
	write(2, "not a valid identifier", 22);
	write(2, "\n", 1);
	g_all->staus_code = 1;
}

int	check_syntax_export_false(t_commands *tmp, int k, int lenarg)
{
	int	i;

	i = 0;
	while (tmp->arguments[k][i])
	{
		if (ft_isalpha(tmp->arguments[k][i]) == 1
		|| tmp->arguments[k][i] == '_')
			i++;
		else if ((ft_isdigit2(tmp->arguments[k][i]) == 1
			&& i != 0 ) || tmp->arguments[k][i] == '_')
			i++;
		else
		{
			error_syntax(tmp, k);
			g_all->staus_code = 1;
			return (1);
		}
	}
	return (0);
}

int	check_syntax_export_true(t_commands *tmp, int k, int lenarg)
{
	int	i;

	i = 0;
	while (tmp->arguments[k][i] != '=')
	{
		if (ft_isalpha(tmp->arguments[k][i]) == 1
		|| tmp->arguments[k][i] == '_')
			i++;
		else if ((ft_isdigit2(tmp->arguments[k][i]) == 1
			&& i != 0 ) || tmp->arguments[k][i] == '_')
			i++;
		else
		{
			error_syntax(tmp, k);
			g_all->staus_code = 1;
			return (1);
		}
	}
	return (0);
}

int	half_add_env(t_commands *tmp, t_norm norm, char **envp, int k)
{
	char	*s;

	if (ft_strncmp(norm.ef, "\0", 1) == 0)
	{
		envp[norm.i] = ft_strdup(tmp->arguments[k]);
		envp[norm.i + 1] = NULL;
	}
	else
	{
		norm.b += 1;
		norm.te = (tmp->arguments[k] + norm.b);
		norm.lenp = len_of_args(envp);
		norm.i = -1;
		if (loop_add_env(tmp, norm, envp, s) == -100)
			return (-100);
	}
	return (0);
}

void	add_in_env(t_commands *tmp, int k, char **envp)
{
	t_norm	norm;

	norm.lenp = 0;
	norm.i = 0;
	norm.b = 0;
	norm.c = 0;
	while (tmp->arguments[k][norm.b] != '=')
		norm.b++;
	norm.varibale = malloc(sizeof(char) * norm.b + 1);
	while (norm.c != norm.b)
	{
		norm.varibale[norm.c] = tmp->arguments[k][norm.c];
		norm.c++;
	}
	norm.varibale[norm.c] = '\0';
	norm.ef = search_in_env2(norm.varibale, envp);
	while (envp[norm.i] != NULL)
		norm.i++;
	if (half_add_env(tmp, norm, envp, k) == -100)
	{
		free(norm.ef);
		return ;
	}
	free(norm.ef);
	free(norm.varibale);
}
