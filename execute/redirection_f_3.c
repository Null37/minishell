/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_f_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:36:48 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/25 20:35:16 by rel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	half_lnf(t_filerdr **head, t_filerdr **last, t_norm *norm)
{
	char	*err;

	norm->fd_l = open((*head)->name, O_RDONLY);
	if (norm->fd_l < 0)
	{
		err = strerror(errno);
		write(2, "minishell: ", 11);
		write(2, (*head)->name, ft_strlen((*head)->name));
		write(2, ": ", 2);
		ft_putstr_fd(err, 2);
		write(2, "\n", 1);
		return (0);
	}
	*last = *head;
	close(norm->fd_l);
	return (1);
}

void	half_lnf_otw(t_filerdr **head, t_filerdr **last, t_norm *norm)
{
	if ((*head)->type == 1)
	{
		norm->fd_l = open((*head)->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		*last = *head;
		close(norm->fd_l);
	}
	else if ((*head)->type == 2)
	{
		norm->fd_l = open((*head)->name, O_CREAT, 0644);
		*last = *head;
		close(norm->fd_l);
	}
}

t_filerdr	*last_name_func(t_commands *tmp)
{
	t_filerdr	*head;
	t_filerdr	*last;
	t_norm		*norm;

	norm = malloc(sizeof(t_norm));
	norm->fd_l = -70;
	head = tmp->filerdr;
	while (1)
	{
		if (head->type == 0)
		{
			if (half_lnf(&head, &last, norm) == 0)
			{
				free(norm);
				return (NULL);
			}
		}
		half_lnf_otw(&head, &last, norm);
		if (!head->next)
			break ;
		head = head->next;
	}
	free(norm);
	return (last);
}
