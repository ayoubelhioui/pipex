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
SRC = pipex.c includes/get_next_line.c includes/get_next_line_utils.c \
helper_files/ft_putstr_fd.c helper_files/ft_split.c \
helper_files/ft_strcmp.c helper_files/ft_strncmp.c \
pipex_utils.c helper_files/ft_substr.c pipex_utils_helper.c
NAME = pipex

all:$(NAME)
$(NAME): $(SRC)
	@$(CC) $(CFLAGS) -c $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)
bonus : $(NAME)
clean :
	@rm -f *.o
fclean: clean
	@rm -f $(NAME)
re:fclean all