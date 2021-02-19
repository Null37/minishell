/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:51:08 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/14 18:35:34 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int n)
{
	int		i;
	char	*p;

	p = (char *)str;
	i = ft_strlen(str);
	while (i - 1 >= 0 && p[i] != n)
	{
		i--;
	}
	if (p[i] == n)
	{
		return (p + i);
	}
	else
		return (NULL);
}
