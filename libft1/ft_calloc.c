/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:34:17 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/18 09:46:45 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char		*p;
	size_t		i;

	i = 0;
	p = malloc(count * size);
	if (!p)
		return (NULL);
	while (i < count * size)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
