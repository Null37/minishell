/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:49:28 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/26 16:08:47 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell_hr.h"

static int	word_count(const char *str, char c)
{
	int	len;
	int	count;

	len = 1;
	count = 0;
	while (*str)
	{
		if (*str == c)
			len = 0;
		else if (len == 1)
			count++;
		len++;
		str++;
	}
	return (count);
}

static char	*copy_word(char const *str, int *i, char c)
{
	int		j;
	int		len;
	char	*word;

	j = *i;
	len = 0;
	while (str[j] != c && str[j])
	{
		len++;
		j++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (str[*i] && str[*i] != c)
	{
		word[j] = str[*i];
		*i = *i + 1;
		j++;
	}
	word[j] = '\0';
	return (word);
}

static	void	ft_free(char ***pm, int *j)
{
	while (*j >= 0)
	{
		free(**(pm + *j));
		*j = *j - 1;
	}
	free(*pm);
}

char	**ft_split(char const *str, char c)
{
	t_libftn	lib;

	lib.i2 = 0;
	lib.j = 0;
	if (!str)
		return (NULL);
	lib.pm = (char **)malloc(sizeof(char *) * (word_count(str, c) + 1));
	if (lib.pm == NULL)
		return (NULL);
	while (str[lib.i2] && lib.j < word_count(str, c))
	{
		if (str[lib.i2] != c)
		{
			lib.pm[lib.j++] = copy_word(str, &lib.i2, c);
			if (lib.pm == NULL)
			{
				ft_free(&lib.pm, &lib.j);
				return (NULL);
			}
		}
		else
			lib.i2++;
	}
	lib.pm[lib.j] = NULL;
	return (lib.pm);
}
