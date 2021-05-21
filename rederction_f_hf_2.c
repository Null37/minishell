/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederction_f_hf_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:11:25 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/21 11:24:18 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

int	check_fname(int r, char *s, int *i)
{
	int	b;
	int	v;

	b = 1;
	if (r == 2)
		(*i)++;
	if (s[*i] == ';' && (s[*i + 1] == ' ' || s[(*i) + 1] == '\0'))
		return (*i);
	while (s[++(*i)])
	{
		if (s[*i] == ' ')
			continue ;
		v = half_check_name(s, i, &b);
		if (v != -666)
			return (v);
		v = half_check_fn(i, &b, s);
		if (v != -666)
			return (v);
	}
	v = err_b(b);
	if (v != -666)
		return (v);
	return (0);
}

int	check_pipp_sy(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 32)
			continue ;
		else if ((s[i] == '|' && s[i + 1] != '|')
			|| (s[i] == ';' && s[i + 1] != ';'))
		{
			write(2, "minishell: syntax ", 18);
			write(2, "error near unexpected token", 27);
			write(2, "`", 1);
			write(2, &s[i], 1);
			write(2, "'", 1);
			write(2, "\n", 1);
			g_all->staus_code = 258;
			return (-1);
		}
		else
			break ;
	}
	return (0);
}

int	check_syntax_number(char *av, int i, int r)
{
	while (av[++i])
	{
		if (ft_isdigit(av[i]) == 1)
			continue ;
		else if (r == 2 && (av[i + 1] == '>' || av[i + 1] == '<'))
			return (-1);
		else if (r <= 1 && (av[i] == '>' || av[i] == '<'))
			return (-1);
		else if (av[i] == 32 || ft_isascii(av[i]) == 1)
			return (0);
	}
	return (0);
}

int	half_check_syn_r(int *i, char *av)
{
	if (av[*i] == 34)
	{
		if (skip_double_coats(av, i) == 1)
		{
			write(2, "minishell: not in subject", 25);
			write(2, "\n", 1);
			g_all->staus_code = 1;
			return (-1);
		}
	}
	else if (av[*i] == 39)
	{
		if (skip_single_coats(av, i) == 1)
		{
			write(2, "minishell: not in subject", 25);
			write(2, "\n", 1);
			g_all->staus_code = 1;
			return (-1);
		}
	}
	return (-666);
}

void	errr_r2(void)
{
	write(2, "minishell: not in subject", 25);
	write(2, "\n", 1);
	g_all->staus_code = 1;
}
