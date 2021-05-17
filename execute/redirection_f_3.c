/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_f_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:36:48 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/17 11:51:34 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

t_filerdr	*last_name_func(t_commands *tmp)
{
	t_filerdr *head;
	t_filerdr *last;
	t_norm	*norm;

	norm = malloc(sizeof(t_norm));
	char *err;

	norm->fd_l = -70;
	head = tmp->filerdr;
	while (1)
	{
		if (head->type == 0)
		{
			norm->fd_l = open(head->name, O_RDONLY);
			if (norm->fd_l < 0)
			{
				err = strerror(errno);
				write(2, "minishell: ", 11);
				write(2, head->name, ft_strlen(head->name));
				write(2, ": ", 2);
				ft_putstr_fd(err, 2);
				write(2, "\n", 1);
				return (NULL);
			}
			last = head;
			close(norm->fd_l);
		}
		else if (head->type == 1)
		{
			norm->fd_l = open(head->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			last = head;
			close(norm->fd_l);
		}
		else if (head->type == 2)
		{
			norm->fd_l = open(head->name, O_CREAT, 0644);
			last = head;
			close(norm->fd_l);
		}
		if (!head->next)
			break ;
		head = head->next;
	}
	return (last);
}
