/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_f_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:36:48 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/27 16:57:39 by fbouibao         ###   ########.fr       */
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

int	half_lnf_otw(t_filerdr **head, t_filerdr **last, t_norm *norm)
{
	if (ft_strncmp((*head)->name, "", 1) == 0)
	{
		write(2, "minishell: ", 11);
		write(2, (*head)->name, ft_strlen((*head)->name));
		write(2, ": ", 2);
		ft_putstr_fd("No such file or directory", 2);
		write(2, "\n", 1);
		return (0);
	}
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
	return (1);
}

int	loop_lnf(t_filerdr **head, t_filerdr **last, t_norm **norm)
{
	while (1)
	{
		if ((*head)->type == 0)
		{
			if (half_lnf(head, last, *norm) == 0)
			{
				free(*norm);
				return (1);
			}
		}
		if (half_lnf_otw(head, last, *norm) == 0)
		{
			free(*norm);
			return (1);
		}
		if (!(*head)->next)
			break ;
		(*head) = (*head)->next;
	}
	return (0);
}

t_filerdr	*last_name_func(t_commands *tmp)
{
	t_filerdr	*head;
	t_filerdr	*last;
	t_norm		*norm;
	int			o;

	norm = malloc(sizeof(t_norm));
	norm->fd_l = -70;
	head = tmp->filerdr;
	o = loop_lnf(&head, &last, &norm);
	if (o == 1)
		return (NULL);
	free(norm);
	return (last);
}
