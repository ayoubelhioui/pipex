# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 18:12:25 by ael-hiou          #+#    #+#              #
#    Updated: 2022/01/27 15:38:49 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = @gcc
RM = @rm -f
CLIB = @ar rc
CFLAGS = -Wextra -Werror -Wall
SRC = ft_atoi.c ft_calloc.c ft_bzero.c ft_strncmp.c ft_itoa.c ft_split.c
NAME = libft.a
OBJECTFILE = $(SRC:.c=.o)
BONUSC = ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstnew_bonus.c ft_lstlast_bonus.c
BONUSO = $(BONUSC:.c=.o)


all : $(NAME)

$(NAME) : $(OBJECTFILE)
	$(CLIB) $(NAME) $(OBJECTFILE)
bonus : $(BONUSO)
	$(CLIB) $(NAME) $(BONUSO)
clean: 
	$(RM) $(OBJECTFILE)
	$(RM) $(BONUSO)
fclean : clean
	$(RM) $(NAME)
re : fclean all bonus
