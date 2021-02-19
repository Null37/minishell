/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:32:59 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/18 23:22:31 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t lendest;
	size_t lensrc;
	size_t save;
	size_t i;

	i = 0;
	save = 0;
	lensrc = ft_strlen(src);
	if (dest == NULL && size == 0)
		return (size + lensrc);
	lendest = ft_strlen(dest);
	if (lendest <= size)
		save = lensrc + lendest;
	if (lendest >= size)
		save = lensrc + size;
	while (src[i] != '\0' && lendest + 1 < size)
	{
		dest[lendest] = src[i];
		i++;
		lendest++;
	}
	if (i != 0)
		dest[lendest] = '\0';
	return (save);
}
