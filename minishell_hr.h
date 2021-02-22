/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_hr.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:38:42 by ssamadi           #+#    #+#             */
/*   Updated: 2021/02/21 19:30:32 by ssamadi          ###   ########.fr       */
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
int len_of_args(char **args);
t_commands   *g_commands;