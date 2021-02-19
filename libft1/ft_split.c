/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:49:28 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/21 10:48:51 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		word_count(const char *str, char c)
{
	int len;
	int count;

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

static	char	*copy_word(char const *str, int *i, char c)
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
	if (!(word = (char *)malloc(sizeof(char) * (len + 1))))
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

char			**ft_split(char const *str, char c)
{
	int				i;
	int				j;
	char			**pm;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (!(pm = (char **)malloc(sizeof(char *) * (word_count(str, c) + 1))))
		return (NULL);
	while (str[i] && j < word_count(str, c))
	{
		if (str[i] != c)
		{
			if ((pm[j++] = copy_word(str, &i, c)) == NULL)
			{
				ft_free(&pm, &j);
				return (NULL);
			}
		}
		else
			i++;
	}
	pm[j] = NULL;
	return (pm);
}
