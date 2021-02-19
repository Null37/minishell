/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:34:17 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/16 21:00:33 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char		*p;
	size_t		i;

	i = 0;
	if ((!(p = malloc(count * size))))
		return (NULL);
	while (i < count * size)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
