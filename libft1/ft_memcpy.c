/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:53:09 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/17 14:12:14 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t nb)
{
	char		*p1;
	char		*p2;
	size_t		i;

	i = 0;
	p1 = (char *)dst;
	p2 = (char *)src;
	if (dst == src)
		return (dst);
	while (i < nb)
	{
		p1[i] = p2[i];
		i++;
	}
	return (dst);
}
