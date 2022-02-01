# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 16:12:46 by marvin            #+#    #+#              #
#    Updated: 2022/01/26 16:12:46 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror -Wall
SRC = pipex.c includes/get_next_line.c includes/get_next_line_utils.c 
NAME = pipex
LIBFT = libft/libft.a

all:$(NAME)
$(NAME):
	@cd libft && make && make bonus && cd ..
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)
clean:
	@cd libft && make clean && cd ..
fclean:clean
	@rm -f $(NAME)
re:fclean all