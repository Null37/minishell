/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_hr.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:38:42 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/23 20:28:20 by fbouibao         ###   ########.fr       */
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

typedef struct		s_tmp{
	char *s1;
	char *s2;
	int i;
	int j;
	char *ss;
	char	*rstr;
	int k;
	char *test;
	int z;
	char *s;
	int lenp;
	char *buff;
	char *fsf;
}					t_tmp;

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
	int start;//*
	int i;//*
	char *buf;//*
	t_commands *tpp;//*
	char *ptr;//*
}					t_env;

typedef struct		s_rdr
{
	int i;
	int start;
	int k;
	int b;
	char *rdr_cmd;
	char *str;
	char *t;
	t_filerdr *tmp;
}					t_rdr;

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
			int pipe_err;
			int	option;
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
	char	*n_tmp;
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
	int g;
	int fd_l;
	int read_fd;
	int fd_pipe[2];
	int write_fd;
	int	file;
	int fd_input;
	int fd_out;
	int	pipe_ch;
	int     start;//*
	t_commands  *tmp;//*
	char *cmd;//*
	char *cmd_tmp;//*
	char **envp;//*
}		t_norm;

t_commandg *g_all;

void	err_this_command(t_commands *tmp, int pipe);
int	check_syntax_number(char *av, int i, int r);
int	half_check_syn_r(int *i, char *av);
int	check_pipp_sy(char *s);
void	errr_r2(void);
int	valid_rdr(char c);
int	check_fname(int r, char *s, int *i);
int	check_rdr(char *s, int i);
void	parssing_shell(char *ptr, t_env *evp, char *cmds);
int our_command(t_commands *tmp, char *ptr, t_env *evp);
void  ur_command_pipe(t_commands *tmp, char *ptr, char **envp);
int	check_this_command(t_commands *tmp, t_env *evp, int pipe);
int	valid_type(char c0, char c1, char c2);
int	err_b(int b);
int         nbr_argts2(char *command);
int		my_strcmp(char *s1, char *s2);
int           nbr_argts(t_commands *commands);
char		*search_in_env2(char *variable, char **envp);
void	sort_algo(t_env *evp);
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
int check_if_command_is_exist(char *path_file, int exute, int pipe);
int		spcle_chr(char c);
char    *ft_strjoinchar(char *s, char c);
int             get_char();
char *termcap_khedma(t_history *history);
int	half_check_fn(int *i, int *b, char *s);
int	half_check_name(char *s, int *i, int *b);
t_history	*new_commnd(char *cmd);
t_filerdr *last_name_func(t_commands *tmp);
int	half_loop(char *av, int i, int v, int r);
int	half_r4(int *i, char *av);
int	half_syn_r3(char *av, int *i, int r);
int	half_check_syn_r2(int *i, char *av);
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
void print_error_check_commd(t_commands *tmp, int pipe);
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
int	half_check_c_2(t_commands *tmp, t_norm norm, int pipe);
void	free_cmds(char **cmd);
int	half_check_commad(t_commands *tmp, char *path, int pipe);
t_filerdr	*last_name_func(t_commands *tmp);
void	half_rid_zerot_commands(t_filerdr *lastnamef, t_norm *norm);
void	half_pip_rid_one(t_norm *norm, t_filerdr *lastnamef);
void	normal_pipe(t_norm	*norm);
void	reset(t_norm *norm, char *ptr);
void	parent(t_norm *norm, t_commands *tmp);
int		half_else_exu(t_commands *tmp, t_env *evp);
void	pip_rid_one(t_commands *tmp, t_filerdr *lastnamef,
	t_env *evp, t_norm *norm);
void	start_pipe(t_norm *norm);
int        get_commands(char *ptr, t_env *evp, t_commands **commands, char *cmds);//*
t_commands  *new_commands();//*
char	*deletespace(char *str);//*
int	split_pipe(char **envp, t_commands *commands);//*
t_commands	*norm_commands1(char *cmds, t_env *evp, t_commands *commands, int i);//*
void        trait_command(char **envp, t_commands *commands);//*
void        split_command_rdr(char **envp, t_commands *commands, int nbr_args); //*
char		*deleterdr(char *command);//*
void add_null(t_commands *cmd, int nbr);//*
char *deletecoats(char **envp, char *str);//*
int check_echo_n(char *s);//*
int		files_rdr(t_commands *commands);//*
t_filerdr	*new_files_rdr();//*
int		get_type_rdr(char *command, int i);//*
char	*get_rdr_file(char *command, int i);//*
int		skip_filename(char *cmds, int *i);//*
char	*get_rdr_file(char *command, int i);//*
char		*deleterdr(char *command);//*
char *deletecoats(char **envp, char *str);//*
char	*getdblcoat(char **envp, char *rstr, char *str, t_tmp *tmp);//*
char	*getsglcoat(char *rstr, char *str, t_tmp *tmp);//*
char	*add_vrbs(char **envp, char *str, t_tmp *tmp, char *typ);//*
char	*my_substr2(char *s, int start, int end);//*
int syntax(char ch, int i);//*
char *search_in_env(char *variable, char **envp);//*
int        check_cmd(char *cmnd);//*