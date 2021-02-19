/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:00:26 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/20 16:01:49 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *p;
	t_list *store;

	if (lst != NULL && del != NULL)
	{
		store = *lst;
		while (store != NULL)
		{
			p = store;
			store = store->next;
			del(p->content);
			free(p);
		}
		*lst = NULL;
	}
}
