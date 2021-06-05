/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:15:32 by fbouibao          #+#    #+#             */
/*   Updated: 2021/06/03 11:21:55 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

t_commands	*new_commands(void)
{
	t_commands	*commands;

	commands = malloc(sizeof(t_commands));
	if (!commands)
		return (NULL);
	commands->command = NULL;
	commands->type = NULL;
	commands->arguments = NULL;
	commands->all = NULL;
	commands->filerdr = NULL;
	commands->path = NULL;
	commands->next = NULL;
	commands->next_p = NULL;
	commands->option = 0;
	return (commands);
}

t_filerdr	*new_files_rdr(void)
{
	t_filerdr	*f;

	f = malloc(sizeof(t_filerdr));
	f->error = 0;
	f->name = NULL;
	f->type = -1;
	f->next = NULL;
	return (f);
}

int	syntax(char ch, int i)
{
	if ((ft_isalpha(ch) == 1 && i == 0) || (ch == '_' && i == 0))
	{
		return (1);
	}
	else if ((ft_isalpha(ch) == 1 && i != 0) || (ft_isdigit(ch) == 1 && i != 0))
		return (1);
	return (0);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	size_t	size;
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
		return ((str = ft_strdup(s2)));
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
