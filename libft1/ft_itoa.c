/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:58:01 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/14 15:45:34 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char		*ft_itoa(int nbr)
{
	long long	x;
	int			n;
	int			i;
	char		*str;

	i = numblen(nbr);
	n = 0;
	x = nbr;
	if ((str = (char *)malloc(sizeof(char) * i + 1)) == NULL)
		return (NULL);
	str[i] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		x = x * -1;
		n = 1;
	}
	i--;
	while ((i > 0 && n == 1) || (i >= 0 && n == 0))
	{
		str[i] = x % 10 + 48;
		x /= 10;
		i--;
	}
	return (str);
}
