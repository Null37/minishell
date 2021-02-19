/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:55:04 by ssamadi           #+#    #+#             */
/*   Updated: 2019/11/19 18:31:57 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *p;
	t_list *k;

	k = NULL;
	while (lst != NULL && f != NULL)
	{
		if (!(p = ft_lstnew((f)(lst->content))))
		{
			ft_lstclear(&k, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&k, p);
		lst = lst->next;
	}
	return (k);
}
