/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:09:43 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/19 17:42:47 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	spcle_chr(char c)
{
	if (c == 34 || c == 39 || c == '\\')
		return (1);
	return (0);
}

int	skip_double_coats(char *cmds, int *i)
{
	while (cmds[++(*i)])
	{
		if (cmds[*i] == '\\' && spcle_chr(cmds[(*i) + 1]))
			(*i)++;
		else if (cmds[*i] == 34)
			return (0);
	}
	return (1);
}

int	skip_single_coats(char *cmds, int *i)
{
	while (cmds[++(*i)])
		if (cmds[*i] == 39)
			return (0);
	return (1);
}

char	*my_substr(char *s, int start, int end)
{
	char	*str;
	int		j;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = start;
	while (s[i] != '\0' && i < end)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*my_substr2(char *s, int start, int end)
{
	char	*str;
	int		j;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = start;
	while (s[i] != '\0' && i < end)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(s);
	return (str);
}
