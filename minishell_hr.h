/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_hr.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:38:42 by ssamadi           #+#    #+#             */
/*   Updated: 2021/03/18 10:15:34 by ssamadi          ###   ########.fr       */
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
	int				multiple;
	struct 			s_commands	*next;
}					t_commands;

t_commands   *parssing_shell(char *ptr, char **envp, char *cmds);
int our_command(t_commands *tmp, char *ptr, char **envp);
int check_this_command(t_commands *tmp,char **envp);
int         nbr_argts2(char *command);
int		my_strcmp(char *s1, char *s2);
int           nbr_argts(t_commands *commands);
char		*search_in_env2(char *variable, char **envp);
char **sort_algo(char **sortest);
int len_of_args(char **args);
char		*get_env_name(char *envp);
int    chck_sntx(char *str);
char *g_cmds;
t_commands   *g_commands;