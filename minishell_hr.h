/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_hr.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:38:42 by ssamadi           #+#    #+#             */
/*   Updated: 2021/04/11 11:38:01 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "libft1/libft.h"

typedef struct		s_filerdr{
	char        	*name;
	int	        	type;
	int				error;
	struct 			s_filerdr	*next;
}					t_filerdr;

typedef struct		s_commands{
	char        	*command;
	char        	*type;
	char			*path;
	int				pid;
	int         	option;
	char        	**arguments;
	int				multiple;
	char        	**all;
	t_filerdr		*filerdr;
	struct 			s_commands	*next_p;
	struct 			s_commands	*next;
}					t_commands;

typedef struct		s_env
{
	char **my_env;
}					t_env;

int redir_fd_in;
int redir_fd;
int yesdup;

t_commands   *parssing_shell(char *ptr, t_env *evp, char *cmds);
int our_command(t_commands *tmp, char *ptr, t_env *evp);
void  ur_command_pipe(t_commands *tmp, char *ptr, char **envp);
int check_this_command(t_commands *tmp,t_env *evp);
int         nbr_argts2(char *command);
int		my_strcmp(char *s1, char *s2);
int           nbr_argts(t_commands *commands);
char		*search_in_env2(char *variable, char **envp);
char **sort_algo(char **sortest);
int len_of_args(char **args);
char		*get_env_name(char *envp);
char **copy_envp(char **envp);
int    chck_sntx(char *str);
void command_cd(t_commands *tmp, char **env);
void command_pwd(char *ptr);
void command_exit(t_commands *tmp, int pipe);
void command_env(char **envp);
void command_export(t_commands *tmp, t_env *evp);
void command_unset(t_commands *tmp ,t_env *evp);
void command_echo(t_commands *tmp);
void  pipe_commmand_c(t_commands *tmp, char *ptr, t_env *evp);
void se_execute_command(t_commands *tmp, char *ptr, t_env *evp);
char	*my_substr(char *s, int start, int end);
int		skip_double_coats(char *cmds, int *i);
int		skip_single_coats(char *cmds, int *i);
int check_syntax_rederction(char *av);
void check_syntax(t_commands *tmp,int k, int lenarg, char e_u);
void	mini_redrection(t_commands *tmp, char *ptr,t_env *evp);
char *g_cmds;
int pid;
int fuck;
t_commands   *g_commands;