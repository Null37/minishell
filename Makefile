# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 08:26:47 by ssamadi           #+#    #+#              #
#    Updated: 2021/04/07 18:44:25 by ssamadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -fsanitize=address

SRC = minishell.c parsing.c algo_sort.c rederction_test2.c

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