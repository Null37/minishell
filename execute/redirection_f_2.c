/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_f_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:34:12 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/27 12:47:50 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	check_two_red(t_commands *tmp)
{
	t_filerdr	*head;
	int			cpt;
	int			cpt2;

	cpt = 0;
	cpt2 = 0;
	head = tmp->filerdr;
	while (1)
	{		
		if (head->type == 0)
			cpt = 1;
		else if (head->type == 1)
			cpt2 = 1;
		else if (head->type == 2)
			cpt2 = 1;
		if (!head->next)
			break ;
		head = head->next;
	}
	if (cpt == 1 && cpt2 == 1)
		return (1);
	return (0);
}

void	err_input(t_filerdr	*head)
{
	char	*err;

	err = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, head->name, ft_strlen(head->name));
	write(2, ": ", 2);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
}

int	input_ret(t_commands *tmp)
{
	t_filerdr	*head;
	int			fd;

	head = tmp->filerdr;
	fd = -12;
	while (1)
	{
		if (head->type == 0)
		{
			close(fd);
			fd = open(head->name, O_RDONLY);
			if (fd < 0)
			{
				err_input(head);
				return (-100);
			}
		}
		if (!head->next)
			break ;
		head = head->next;
	}
	return (fd);
}
