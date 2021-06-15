# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiari <abiari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 08:41:04 by abiari            #+#    #+#              #
#    Updated: 2021/06/15 20:00:31 by abiari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

SRC = pipex.c utils/env_utils.c utils/envp_to_envl.c utils/lst_append.c\
check_exec.c pipes.c pipes_helper.c

OBJ = $(SRC:.c=.o)

SRC_BONUS = pipex_bonus.c utils_bonus/env_utils_bonus.c\
utils_bonus/envp_to_envl_bonus.c utils_bonus/lst_append_bonus.c\
check_exec_bonus.c pipes_bonus.c pipes_helper_bonus.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME):
	make fclean -C ./libft && make -C ./libft &&\
	make bonus -C ./libft && make clean -C ./libft
	$(CC) $(CFLAGS) $(SRC) libft/libft.a -o $(NAME)

bonus:
	make fclean -C ./libft && make -C ./libft &&\
	make bonus -C ./libft && make clean -C ./libft
	$(CC) $(CFLAGS) $(SRC_BONUS) libft/libft.a -o $(NAME)

clean:
	/bin/rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
