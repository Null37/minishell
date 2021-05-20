/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:20:17 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/18 11:57:17 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(src) == 0)
		return ((char *)dst);
	if (len == 0)
		return (0);
	while (dst[i] != '\0' && i < len)
	{
		j = 0;
		while (dst[i + j] == src[j] && i + j < len)
		{
			j++;
			if (src[j] == '\0')
				return ((char *)&dst[i]);
		}
		i++;
	}
	return (0);
}
