/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:56:01 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/17 16:21:24 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t numbpyt)
{
	char			*p1;
	char			*p2;
	size_t			j;

	p1 = (char *)dst;
	p2 = (char *)src;
	j = 0;
	if (p1 == p2)
		return (p1);
	if (p1 < p2)
		return ((char *)ft_memcpy(p1, p2, numbpyt));
	else
	{
		while (numbpyt > 0)
		{
			p1[numbpyt - 1] = p2[numbpyt - 1];
			numbpyt--;
		}
	}
	return (dst);
}
