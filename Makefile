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
SRC = pipex.c includes/get_next_line.c includes/get_next_line_utils.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strcmp.c libft/ft_strncmp.c
NAME = pipex

all:$(NAME)
$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -g
clean:
	 
fclean:clean
	@rm -f $(NAME)
re:fclean all