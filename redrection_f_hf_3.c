/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redrection_f_hf_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:13:38 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/21 11:29:55 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

int	err_b(int b)
{
	if (b == 1)
	{
		write(2, "minishell: syntax error near ", 29);
		write(2, "unexpected token `newline'", 26);
		write(2, "\n", 1);
		g_all->staus_code = 258;
		return (-1);
	}
	return (-666);
}

int	half_check_fn(int *i, int *b, char *s)
{
	if (s[*i] != '|' && s[*i] != '>' && s[*i] != ';' && s[*i] != '<')
		return (--(*i));
	else if (valid_rdr(s[*i]) == -1)
	{
		if (valid_type(s[*i - 1], s[*i], s[*i + 1]) == -1)
		{
			*b = 0;
			return (-1);
		}
	}
	return (-666);
}

int	half_check_name(char *s, int *i, int *b)
{
	if (s[*i] == 34)
	{
		if (skip_double_coats(s, i) == 1)
		{
			*b = 0;
			return (-6);
		}
		return (*i);
	}
	else if (s[*i] == 39)
	{
		if (skip_single_coats(s, i) == 1)
		{
			*b = 0;
			return (-6);
		}
		return (*i);
	}
	return (-666);
}
