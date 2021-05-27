# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 08:26:47 by ssamadi           #+#    #+#              #
#    Updated: 2021/05/27 14:42:23 by fbouibao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS =  -lcurses -Wall -Wextra -Werror -fsanitize=address

SRC = minishell.c parsing.c rederction_f.c \
termcap_fl.c execute/funct_file.c \
execute/cmd_cd_function.c \
execute/edit_envp.c \
execute/file_check_path.c \
execute/file_check_path2.c \
execute/env_1.c \
execute/env_2.c \
execute/env_3.c execute/env_4.c\
execute/all_command.c execute/signal.c\
execute/mini_func.c execute/mini_func_2.c \
execute/env_5.c execute/check_syntax_1.c\
execute/env_6.c\
execute/redirection_f_1.c\
execute/redirection_f_2.c\
execute/unset.c\
execute/of_redirection.c \
execute/redirection_f_3.c \
execute/of_pipe.c \
execute/of_pipe_fuc.c \
execute/of_pipe_fuc_2.c \
parsing/get_command.c\
parsing/get_command_cnt.c\
parsing/split_pipe.c\
parsing/split_command_rdr.c\
parsing/files_rdr.c\
parsing/get_rdr_file.c\
parsing/deleterdr.c\
parsing/deletecoats.c\
parsing/parsing_tools.c\
parsing/parsing_tools2.c\
parsing/coats_file.c\
parsing/add_vrbs.c\
parsing/reda_tools.c\
parsing/skip_filename.c\
parsing/serch_i_e.c\
rederction_f_hf_1.c\
rederction_f_hf_2.c\
redrection_f_hf_3.c\
parsing/convert_vrbs_file.c\
parsing/trait_command.c\
execute/mor_fun_ac.c\
execute/mor_fun_env_6.c\
key_termcap.c\
key_2.c

CC = gcc

all: libft1 $(NAME)

$(NAME): $(SRC)
	cp ./libft1/libft.a .
	$(CC) -g $(FLAGS) $(SRC) libft.a -o $(NAME)

libft1:
	cd libft && $(MAKE) clean

clean: libftclean

libftclean:
	$(MAKE)	-C libft1 clean

fclean: clean
	rm $(NAME) libft.a 
	
re: fclean all