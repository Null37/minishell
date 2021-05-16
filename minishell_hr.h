/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_hr.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:38:42 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/16 18:12:16 by ssamadi          ###   ########.fr       */
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
# include <termios.h>
# include <termcap.h>
#include "libft1/libft.h"
# define KEY_UP 183
# define KEY_DOWN 184
# define KEY_LEFT  186
# define KEY_RIGHT 185
# define ENTER 10
# define KEY_REMOVE 127
# define KEY_TAB 9
# define CTRL_D 4

typedef struct		s_history{
	char        	*cmd;
	struct 			s_history	*preview;
	struct 			s_history	*next;
}					t_history;

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
	pid_t resul;
	char        	**all;
	t_filerdr		*filerdr;
	struct 			s_commands	*next_p;
	struct 			s_commands	*next;
}					t_commands;

typedef struct		s_env
{
	char **my_env;
	char *save;
}					t_env;

typedef struct		s_commandg
{
			char* line;
			int staus_code;
			int ctrl_c;
			char *ret;
			int ctrl_quit;
			char *type;
			char *old_pwd;
			int redir_fd_in;
			int redir_fd;
			int yesdup;
}					t_commandg;

typedef struct s_nor
{
	int		lenp;
	char	*nameenv;
	int		j;
	int		i;
	int		len;
	char	*s;
	char *v;
	int t;
	int tee;
	char *te;
	char *buff;
	char *fsf;
	int o;
	int h;
	int b;
	int c;
	char *varibale;
	char *ef;
	int			fd;
	int			fd_check;
	char	*sh;
	char	*tmp;
	char	*newsh;
	int lenarg;
	int k;
	int z;
	char **tprr;
	int fs;
	int ck;
	char **com_path;
	char *path;
	int saved_stdout;
	int saved_input;
	int fd_in;
	int fd_o;
	char *ptr2;
}		t_norm;

t_commandg *g_all;

int test[2];
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
void command_cd(char *ptr,t_commands *tmp, t_env *evp);
void command_pwd(char *ptr, t_env *evp);
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
char		*ft_strjoin1(char *s1, char *s2);
char **edit_envp_pwd(char *ptr, char **envp_c);
int check_if_command_is_exist(char *path_file, int exute);
int		spcle_chr(char c);
char    *ft_strjoinchar(char *s, char c);
int             get_char();
char *termcap_khedma(t_history *history);
t_history	*new_commnd(char *cmd);
t_filerdr *last_name_func(t_commands *tmp);
void command_c(int signum);
int output_ret(t_commands *tmp);
int input_ret(t_commands *tmp);
int check_two_red(t_commands *tmp);
int is_equl(int i, char **envp);
int count_arg_2(t_commands *tmp);
void ft_putchar(char *str);
void command_in_the_sys(t_commands *tmp, char **envp);
void	error_execve(t_commands *tmp);
char **edit_evp_new_oldpwd(char *ptr, char **envp_c);
char	**edit_envp_shlvl(char **envp_c);
void print_error_check_commd(t_commands *tmp);
char	**edit_envp_old_pwd(char **envp_c);
char	**edit_envp_v(char **envp_c);
void	ok_write(char **my_env, int i, int j);
void	add_double_quotes(char **my_env);
int	check_syntax_export_true(t_commands *tmp, int k, int lenarg);
int	check_syntax_export_false(t_commands *tmp, int k, int lenarg);
int	ft_isdigit2(char number);
void add_in_env(t_commands *tmp, int k, char **envp);
int our_command(t_commands *tmp, char *ptr, t_env *evp);
void	mini_redrection(t_commands *tmp, char *ptr,t_env *evp);
void	cntrol_quit(int quit);
int	syntax_true(t_commands *tmp, char **envp, int k, int lenarg);
void add_in_exp(t_commands *tmp, int k, char **my_env);
int check_file_or_dit(char *path_file);
int check_permissions(char *path_file, struct stat stats, int exute);
int	check_file_or_dit(char *path_file);
void	command_unset(t_commands *tmp , t_env *evp);
t_norm *new_norm(char **envp_c);
char  **set_norm(t_norm *norm, char *ptr, char **envp_c);
int	half_check_c_2(t_commands *tmp, t_norm norm);
void	free_cmds(char **cmd);
int	half_check_commad(t_commands *tmp, char *path);
char *g_cmds;
int pid;
int fuck;
t_commands   *g_commands;