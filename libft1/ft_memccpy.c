/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:45:48 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/18 23:39:17 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst1;
	unsigned char	*src1;
	size_t			i;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && src1[i] != (unsigned char)c)
	{
		dst1[i] = src1[i];
		i++;
	}
	if (src1[i] == (unsigned char)c)
	{
		dst1[i] = src1[i];
		return (&dst1[i + 1]);
	}
	return (NULL);
}
