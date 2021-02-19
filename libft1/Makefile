# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssamadi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/09 15:13:12 by ssamadi           #+#    #+#              #
#    Updated: 2019/11/19 18:28:00 by ssamadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
.PHONY = all clean fclean re bonus

NAME=libft.a

FLAGS = -Wall -Wextra -Werror

SRC =  ft_memset.c\
	    ft_bzero.c\
	    ft_memcpy.c\
	    ft_memccpy.c\
	    ft_memmove.c\
	    ft_memchr.c\
	    ft_memcmp.c\
	    ft_strlen.c\
	    ft_isalpha.c\
	    ft_isdigit.c\
	    ft_isalnum.c\
	    ft_isascii.c\
	    ft_isprint.c\
	    ft_toupper.c\
	    ft_tolower.c\
	    ft_strchr.c\
	    ft_strrchr.c\
	    ft_strncmp.c\
	    ft_strlcpy.c\
	    ft_strlcat.c\
	    ft_strnstr.c\
	    ft_atoi.c\
	    ft_calloc.c\
	    ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c

SRC_B =  ft_lstnew_bonus.c\
			ft_lstadd_front_bonus.c\
			ft_lstsize_bonus.c\
			ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c\
			ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c\
			ft_lstiter_bonus.c\
			ft_lstmap_bonus.c

OBJECTS = $(SRC:.c=.o)

OBJECTS_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
			 	 @gcc $(FLAGS) -c $(SRC)
				 @ar rc $(NAME) $(OBJECTS)
				 @ranlib $(NAME)

bonus: $(SRC_B)
				 @gcc $(FLAGS) -c $(SRC_B)
				 @ar rc $(NAME) $(OBJECTS_B)
				 @ranlib $(NAME)

clean:
	@rm -rf $(OBJECTS)  $(OBJECTS_B)

fclean: clean
	@rm -rf $(NAME)

re:	fclean all
