/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:00:20 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/18 11:57:47 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*ss;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	s = (unsigned char *)s1;
	ss = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s[i] != ss[i])
			return (s[i] - ss[i]);
		if (s[i] == '\0' || ss[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
