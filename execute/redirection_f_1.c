/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_f_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:05:51 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/15 15:33:35 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	err_out(t_filerdr	*head)
{
	char	*err;

	err = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, head->name, ft_strlen(head->name));
	write(2, ": ", 2);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
}

int	half_output_ret(t_filerdr	*head, int fd)
{
	if (head->type == 1)
	{
		close(fd);
		fd = open(head->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (head->type == 2)
	{
		close(fd);
		fd = open(head->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	return (fd);
}

int	output_ret(t_commands *tmp)
{
	t_filerdr	*head;
	t_norm		norm;

	norm.fd_check = -50;
	norm.fd = -17;
	head = tmp->filerdr;
	while (1)
	{
		if (head->type == 0)
		{
			norm.fd_check = open(head->name, O_RDONLY);
			if (norm.fd_check < 0)
			{
				err_out(head);
				close(norm.fd_check);
				return (-100);
			}
			close(norm.fd_check);
		}
		norm.fd = half_output_ret(head, norm.fd);
		if (!head->next)
			break ;
		head = head->next;
	}
	return (norm.fd);
}
