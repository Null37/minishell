/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederction_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:13:50 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/24 19:41:07 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

int	valid_rdr(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ';')
		return (-1);
	return (0);
}

int	check_rdr(char *s, int i)
{
	if (s[i] == '>' && s[i + 1] == '>')
		return (2);
	else if (s[i] == '>')
		return (1);
	else if (s[i] == '<')
		return (0);
	return (1);
}

void	err_hvtp(char c0, char c1)
{
	write(2, "minishell: syntax error near unexpected token ", 46);
	write(2, "`", 1);
	write(2, &c0, 1);
	write(2, &c1, 1);
	write(2, "'", 1);
	write(2, "\n", 1);
}

void	hald_valid_tp(char c0, char c1, char c2)
{
	if (c0 == ';' && c1 == ';')
		err_hvtp(c0, c1);
	else if (c1 == '|' && c2 == '|')
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, "`", 1);
		write(2, &c1, 1);
		write(2, &c2, 1);
		write(2, "'", 1);
		write(2, "\n", 1);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, "`", 1);
		write(2, &c1, 1);
		write(2, "'", 1);
		write(2, "\n", 1);
	}
}

int	valid_type(char c0, char c1, char c2)
{
	if (c1 == '>' && c2 == '<')
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, "`", 1);
		write(2, &c1, 1);
		write(2, "'", 1);
		write(2, "\n", 1);
	}
	else if ((c1 == '>' || c1 == '<')
		&& (c2 == '>' || c2 == '<'))
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, "`", 1);
		write(2, &c1, 1);
		write(2, &c2, 1);
		write(2, "'", 1);
		write(2, "\n", 1);
	}
	else
		hald_valid_tp(c0, c1, c2);
	return (-1);
}
