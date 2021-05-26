/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:04:34 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/26 16:13:49 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell_hr.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	t_libftn	lib;

	lib.j3 = 0;
	lib.i3 = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lib.x3 = ft_strlen(s2);
	lib.p = (char *)malloc((ft_strlen(s1) + lib.x3) + 1);
	if (!lib.p)
		return (NULL);
	while (lib.i3 < ft_strlen(s1))
	{
		lib.p[lib.i3] = s1[lib.i3];
		lib.i3++;
	}
	while (lib.j3 < lib.x3)
	{
		lib.p[lib.i3] = s2[lib.j3];
		lib.j3++;
		lib.i3++;
	}
	lib.p[lib.i3] = '\0';
	return (lib.p);
}
