# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:27:47 by abiari            #+#    #+#              #
#    Updated: 2021/06/08 08:32:26 by abiari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memccpy.c ft_memchr.c ft_substr.c ft_tolower.c\
ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c\
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c\
ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c\
ft_tolower.c ft_toupper.c ft_bzero.c ft_atoi.c\
ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isdigit.c\
ft_isprint.c ft_itoa.c ft_isascii.c ft_substr.c ft_strcmp.c\

OBJ = $(SRC:.c=.o)

SRC_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c\
ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c\
ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c\
ft_lstsize_bonus.c\

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

bonus:
	gcc -Wall -Werror -Wextra -c $(SRC_BONUS)
	ar rc $(NAME) $(OBJ_BONUS)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
