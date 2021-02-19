/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:26:07 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/19 16:22:26 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	last = *alst;
	if (!(*alst))
		*alst = new;
	else if (*alst && new)
	{
		while (last != NULL)
		{
			if (last->next == NULL)
			{
				last->next = new;
				break ;
			}
			last = last->next;
		}
	}
}
