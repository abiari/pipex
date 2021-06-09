# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 08:41:04 by abiari            #+#    #+#              #
#    Updated: 2021/06/09 10:03:21 by abiari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

SRC = pipex_bonus.c utils/env_utils_bonus.c utils/envp_to_envl_bonus.c utils/lst_append_bonus.c\
check_exec_bonus.c pipes_bonus.c

all: $(NAME)

$(NAME):
	make -C ./libft && make bonus -C ./libft && make clean -C ./libft
	$(CC) $(CFLAGS) $(SRC) libft/libft.a -o $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
