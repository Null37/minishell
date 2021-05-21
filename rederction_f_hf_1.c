/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederction_f_hf_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:08:51 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/21 11:29:46 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_hr.h"

int	half_check_syn_r2(int *i, char *av)
{
	if (av[*i] == '|')
	{
		*i = check_fname(0, av, i);
		if (*i == -1)
			return (-1);
		else if (*i == -6)
		{
			errr_r2();
			return (-1);
		}
	}
	else if (av[*i] == ';')
	{
		*i = check_fname(0, av, i);
		if (*i == -1)
			return (-1);
		else if (*i == -6)
		{
			write(2, "minishell: not in subject", 25);
			write(2, "\n", 1);
			g_all->staus_code = 1;
			return (-1);
		}
	}
	return (-666);
}

int	half_syn_r3(char *av, int *i, int r)
{
	if ((av[*i] == '>' || av[*i] == '<') && av[(*i) - 1] != '\\')
	{
		r = check_rdr(av, *i);
		if (check_syntax_number(av, *i, r) == -1)
		{
			write(2, "minishell: not in subject\n", 26);
			g_all->staus_code = 1;
			return (-1);
		}
		*i = check_fname(r, av, i);
		if (*i == -1)
			return (-1);
		else if (*i == -6)
		{
			write(2, "minishell: not in subject", 25);
			write(2, "\n", 1);
			g_all->staus_code = 1;
			return (-1);
		}
	}
	return (-666);
}

int	half_r4(int *i, char *av)
{
	(*i)++;
	if (av[*i] == '\0')
	{
		write(2, "minishell: not in subject", 25);
		write(2, "\n", 1);
		g_all->staus_code = 1;
		return (-1);
	}
	if (av[*i] != '\0')
		return (-2);
	return (-666);
}

int	half_loop(char *av, int i, int v, int r)
{
	while (av[++i])
	{
		v = half_check_syn_r(&i, av);
		if (v != -666)
			return (v);
		else if (av[i] == '\\')
		{
			v = half_r4(&i, av);
			if (v != -666 && v != -2)
				return (v);
			if (v == -2)
				continue ;
		}
		v = half_syn_r3(av, &i, r);
		if (v != -666)
			return (v);
		v = half_check_syn_r2(&i, av);
		if (v != -666)
			return (v);
	}
	return (-666);
}

int	check_syntax_rederction(char *av)
{
	int	i;
	int	r;
	int	v;

	i = -1;
	if (check_pipp_sy(av) == -1)
		return (-1);
	v = half_loop(av, i, v, r);
	if (v != -666)
		return (v);
	return (0);
}
