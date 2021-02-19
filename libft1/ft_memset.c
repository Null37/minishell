/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:39:34 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/15 13:45:20 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int source, size_t line)
{
	size_t			nbr;
	unsigned char	*p;

	p = (unsigned char *)str;
	nbr = 0;
	while (nbr < line)
	{
		p[nbr] = source;
		nbr++;
	}
	return (str);
}
