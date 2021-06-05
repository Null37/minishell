/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rdr_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:19:32 by fbouibao          #+#    #+#             */
/*   Updated: 2021/06/05 15:38:43 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	get_last_space(char *str, int i)
{
	while (1)
	{
		if (str[i] != '\\' || i == 0)
			break ;
		i--;
	}
	if (str[i] != '\\')
		i++;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else
			break ;
		i++;
	}
	return (--i);
}

char	*get_right_path(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*path;

	path = malloc((sizeof(char) * (end - start)) + 2);
	if (!path)
		return (NULL);
	i = start - 1;
	j = 0;
	while (++i <= end)
	{
		path[j] = str[i];
		j++;
	}
	path[j] = '\0';
	free(str);
	return (path);
}

void	norm_deletespace(char *str, int *i, int *size, int *start)
{
	*i = -1;
	*size = ft_strlen(str);
	while (++(*i) < (*size))
	{
		if (str[*i] != ' ')
		{
			*start = *i;
			break ;
		}
	}
}

char	*deletespace(char *str)
{
	int	size;
	int	i;
	int	start;
	int	end;

	start = -1;
	end = -1;
	if (!str)
		return (NULL);
	norm_deletespace(str, &i, &size, &start);
	i = size;
	while (--i >= 0)
	{
		if (str[i] != ' ')
		{
			if (str[i] == '\\')
				end = get_last_space(str, i);
			else
				end = i;
			break ;
		}
	}
	if (start == -1 || end == -1)
		return (ft_strdup(""));
	return (get_right_path(str, start, end));
}

char	*get_rdr_file(char *command, int i)
{
	int		start;

	i--;
	start = 0;
	while (command[++i])
	{
		if (command[i] == '>' || command[i] == '<' || command[i] == ' ')
			continue ;
		break ;
	}
	start = i;
	while (i < (int)ft_strlen(command))
	{	
		if (command[i] == 34)
			skip_double_coats(command, &i);
		else if (command[i] == 39)
			skip_single_coats(command, &i);
		else if (command[i] == '\\')
			i++;
		else if (command[i] == '>' || command[i] == '<' || command[i] == ' ')
			break ;
		i++;
	}
	return (deletecoats(deletespace(my_substr(command, start, i))));
}
