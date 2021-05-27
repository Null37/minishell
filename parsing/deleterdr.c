/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleterdr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:40:57 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/27 12:54:50 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	norm_deleterdr(char *command, int *i, char *s, char **comd)
{
	if (command[++(*i)] == '\\')
	{
		s[0] = command[*i];
		*comd = ft_strjoin1(*comd, s);
		(*i)++;
		s[0] = command[*i];
		*comd = ft_strjoin1(*comd, s);
		return (1);
	}
	return (0);
}

char	*deleterdr(char *command)
{
	int		i;
	char	*comd;
	char	*s;

	s = ft_strdup(" ");
	comd = NULL;
	i = -1;
	while (1)
	{	
		if (norm_deleterdr(command, &i, s, &comd))
			continue ;
		else if (command[i] == '>' && command[i + 1] == '>')
			continue ;
		else if ((command[i] == '>' || command[i] == '<'))
			skip_filename(command, &i);
		else
		{
			s[0] = command[i];
			comd = ft_strjoin1(comd, s);
		}
		if (!command[i])
			break ;
	}
	free(s);
	return (comd);
}
