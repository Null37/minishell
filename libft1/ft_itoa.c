/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:58:01 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/26 16:02:00 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell_hr.h"

static int	numblen(long long number)
{
	int			len;

	len = 0;
	if (number < 0)
	{
		number *= -1;
		len++;
	}
	if (number == 0)
	{
		len++;
	}
	while (number > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	t_libftn	lib;

	lib.i = numblen(nbr);
	lib.n = 0;
	lib.x = nbr;
	lib.str = (char *)malloc(sizeof(char) * lib.i + 1);
	if (lib.str == NULL)
		return (NULL);
	lib.str[lib.i] = '\0';
	if (nbr < 0)
	{
		lib.str[0] = '-';
		lib.x = lib.x * -1;
		lib.n = 1;
	}
	lib.i--;
	while ((lib.i > 0 && lib.n == 1) || (lib.i >= 0 && lib.n == 0))
	{
		lib.str[lib.i] = lib.x % 10 + 48;
		lib.x /= 10;
		lib.i--;
	}
	return (lib.str);
}
