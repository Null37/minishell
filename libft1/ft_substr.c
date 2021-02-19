/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:49:58 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/21 11:18:43 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		min(int i, int j)
{
	if (i < j)
		return (i);
	else
		return (j);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		lenmalloc;
	size_t		j;
	char		*m;

	j = start;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		lenmalloc = 0;
	else
		lenmalloc = min(len, ft_strlen(s) - start);
	if (!(m = (char *)malloc(sizeof(char) * lenmalloc + 1)))
		return (NULL);
	while (i < lenmalloc)
	{
		m[i] = s[j];
		i++;
		j++;
	}
	m[i] = '\0';
	return (m);
}
