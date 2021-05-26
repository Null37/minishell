/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:31:43 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/26 16:09:00 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int n)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != n)
	{
		i++;
	}
	if (str[i] == n)
	{
		return ((char *)str + i);
	}
	else
		return (NULL);
}
