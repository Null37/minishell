/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trait_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 19:46:15 by fbouibao          #+#    #+#             */
/*   Updated: 2021/06/04 20:15:05 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	trait_command(t_env *evp, t_commands *commands)
{
	int	i;
	int	nbr_args;

	i = -1;
	nbr_args = 0;
	split_command_rdr(evp, commands, nbr_args);
	files_rdr(evp, commands);
}
