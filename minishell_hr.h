/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_hr.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:38:42 by ssamadi           #+#    #+#             */
/*   Updated: 2021/02/20 11:38:55 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "libft1/libft.h"


typedef struct		s_commands{
	char        	*command;
	char        	*type;
	int         	option;
	char        	**arguments;
	struct 			s_commands	*next;
}					t_commands;

t_commands   *parssing_shell(char *cmds);
int           nbr_argts(t_commands *commands);
t_commands   *g_commands;