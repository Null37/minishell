/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederction_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:13:50 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/20 18:41:56 by ssamadi          ###   ########.fr       */
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
	else if (c0 == ';' && c1 == ';')
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, "`", 1);
		write(2, &c0, 1);
		write(2, &c1, 1);
		write(2, "'", 1);
		write(2, "\n", 1);
	}
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
	return (-1);
}

int	check_fname(int r, char *s, int i)
{
	int	b;

	b = 1;
	if (r == 2)
		i++;
	if (s[i] == ';' && (s[i+1] == ' ' || s[i+1] == '\0'))
		return (i);
	while (s[++i])
	{
		if (s[i] == ' ')
			continue ;
		else if (s[i] == 34)
		{
			if(skip_double_coats(s, &i) == 1)
			{
				b = 0;
				return (-6);
			}
			return (i);
		}
		else if (s[i] == 39)
		{
			if(skip_single_coats(s, &i) == 1)
			{
				b = 0;
				return (-6);
			}
			return (i);
		}
		else if (s[i] != '|' &&  s[i] != '>' && s[i] != ';' && s[i] != '<')
			return (--i);
		else if (valid_rdr(s[i]) == -1)
		{
			if (valid_type(s[i - 1], s[i], s[i + 1]) == -1)
			{
				b = 0;
				return (-1);
			}
		}
	}
	if(b == 1)
	{
		write(2, "minishell: syntax error near unexpected token `newline'", 55);
		write(2, "\n", 1);
		g_all->staus_code = 258;
		return (-1);
	}
	return (0);
}

int	check_pipp_sy(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if(s[i] == 32)
			continue;
		else if((s[i] == '|' && s[i + 1] != '|')|| (s[i] == ';' && s[i + 1] != ';'))
		{
			write(2, "minishell: syntax error near unexpected token ", 46);
			write(2, "`", 1);
			write(2, &s[i], 1);
			write(2, "'", 1);
			write(2, "\n", 1);
			g_all->staus_code = 258;
			return (-1);
		}
		else
			break;
	}
	return (0);
}

int	check_syntax_number(char *av, int i, int r)
{
	while(av[++i])
	{
		if(ft_isdigit(av[i]) == 1)
			continue;
		else if (r == 2 && (av[i + 1] == '>' || av[i + 1] == '<'))
			return (-1);
		else if(r <= 1 && (av[i] == '>' || av[i] == '<'))
			return -1;
		else if(av[i] == 32 || ft_isascii(av[i])  == 1)
			return (0);
	}
	return (0);
}

int	check_syntax_rederction(char *av)
{
	int i;
	int r;

	i = -1;
	if(check_pipp_sy(av) == -1)
		return -1;
	while (av[++i])
	{
		if (av[i] == 34)
		{
			if(skip_double_coats(av, &i) == 1)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				g_all->staus_code = 1;
				return -1;
			}
		}
		else if (av[i] == 39)
		{
			if(skip_single_coats(av, &i) == 1)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				g_all->staus_code = 1;
				return -1;
			}
		}
		else if (av[i] == '\\')
		{
			i++;
			if (av[i] == '\0')
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				g_all->staus_code = 1;
				return -1;
			}
			if (av[i] != '\0')
				continue ;
		}
		if ((av[i] == '>' || av[i] == '<') && av[i - 1] != '\\')
		{
			r = check_rdr(av, i);
			if(check_syntax_number(av, i, r) == -1)
			{
				write(2, "minishell: not in subject\n", 26);
				g_all->staus_code = 1;
				return (-1);
			}
			if ((i = check_fname(r, av, i))== -1)
				return (-1);
			else if(i == -6)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				g_all->staus_code = 1;
				return (-1);
			}
		}
		else if (av[i] == '|')
		{
			if ((i = check_fname(0, av, i))== -1)
				return (-1);
			else if(i == -6)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				g_all->staus_code = 1;
				return (-1);
			}
		}
		else if (av[i] == ';')
		{
			if ((i = check_fname(0, av, i))== -1)
				return (-1);
			else if(i == -6)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				g_all->staus_code = 1;
				return (-1);
			}
		}
	}
	return (0);
}
