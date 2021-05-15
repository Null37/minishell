# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 08:26:47 by ssamadi           #+#    #+#              #
#    Updated: 2021/05/15 16:01:55 by ssamadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS =  -lcurses -fsanitize=address

SRC = minishell.c parsing.c algo_sort.c rederction_test2.c \
termcap_fl.c execute/funct_file.c \
execute/cmd_cd_function.c \
execute/edit_envp.c \
execute/file_check_path.c \
execute/env_1.c \
execute/env_2.c \
execute/env_3.c execute/env_4.c\
execute/all_command.c execute/signal.c\
execute/mini_func.c execute/mini_func_2.c \
execute/env_5.c execute/check_syntax_1.c\
execute/redirection_f_1.c execute/redirection_f_2.c \
execute/unset.c

CC = gcc

all: libft1 $(NAME)


$(NAME): $(SRC)
	cp ./libft1/libft.a .
	$(CC) -g $(FLAGS) $(SRC) libft.a -o $(NAME)

libft1:
	$(MAKE) -C  libft1

clean: libftclean

libftclean:
	$(MAKE)	-C libft1 clean

fclean: clean
	rm $(NAME) libft.a 
	
re: fclean all