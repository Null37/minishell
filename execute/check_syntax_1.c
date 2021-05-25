/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:58:25 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/25 11:43:06 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	err_syn(t_commands *tmp, char e_u, int k)
{
	write(2, "minishell: ", 11);
	if (e_u == 'u')
		write(1, "unset: ", 7);
	else if (e_u == 'e')
		write(1, "export: ", 8);
	write(2, "`", 1);
	write(2, tmp->arguments[k], strlen(tmp->arguments[k]));
	write(2, "'", 1);
	write(2, ": ", 2);
	write(2, "not a valid identifier", 22);
	write(2, "\n", 1);
}

void	check_syntax(t_commands *tmp, int k, int lenarg, char e_u)
{
	int	i;

	i = 0;
	while (tmp->arguments[k][i])
	{
		if (ft_isalpha(tmp->arguments[k][i]) == 1
			|| tmp->arguments[k][i] == '_')
			i++;
		else if ((ft_isdigit2(tmp->arguments[k][i]) && i != 0 )
			|| tmp->arguments[k][i] == '_')
			i++;
		else
		{
			err_syn(tmp, e_u, k);
			g_all->staus_code = 1;
			 break ;
		}
	}
}

void	print_error_check_commd(t_commands *tmp, int pipe)
{
	char	*eir;

	if (pipe == 0)
	{
		eir = strerror(errno);
		write(2, "minishell: ", 11);
		write(2, tmp->type, ft_strlen(tmp->type));
		write(2, ": ", 2);
		write(2, eir, strlen(eir));
		write(2, "\n", 1);
	}
	g_all->staus_code = 127;
}

int	check_if_command_is_exist(char *path_file, int exute, int pipe)
{
	int			fs;
	struct stat	buf;

	fs = stat(path_file, &buf);
	if (exute == 5)
	{
		if (check_file_or_dit(path_file) == 3)
			return (3);
		if (check_permissions(path_file, buf, exute) == 1)
			return (3);
	}
	if (pipe == 0)
	{
		if (fs == 0 || exute == 5)
		{
			if (check_file_or_dit(path_file) == 3)
				return (3);
			if (check_permissions(path_file, buf, exute) == 1)
				return (3);
		}
	}
	return (fs);
}
