/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 20:33:59 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/18 11:57:05 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		i;
	int		j;
	int		n;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (check_char(s1[i], set) && s1[i])
		i++;
	while (check_char(s1[j], set) && j != 0)
		j--;
	if (i > j)
		return (ft_strdup(""));
	p = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!p)
		return (NULL);
	n = 0;
	while (i <= j)
		p[n++] = s1[i++];
	p[n] = '\0';
	return (p);
}
