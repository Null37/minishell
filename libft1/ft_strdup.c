/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:48:36 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/18 12:24:32 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;
	int		x;

	x = ft_strlen(s1);
	i = 0;
	if (!(p = (char *)malloc(x + 1 * sizeof(char))))
		return (NULL);
	while (i < x)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
