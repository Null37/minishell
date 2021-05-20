/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:04:34 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/18 11:59:48 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		x;
	size_t		j;
	char		*p;

	j = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	x = ft_strlen(s2);
	p = (char *)malloc((ft_strlen(s1) + x) + 1);
	if (!p)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		p[i] = s1[i];
		i++;
	}
	while (j < x)
	{
		p[i] = s2[j];
		j++;
		i++;
	}
	free(s1);
	p[i] = '\0';
	return (p);
}
