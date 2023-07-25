# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 13:32:50 by hsawamur          #+#    #+#              #
#    Updated: 2023/07/24 14:55:15 by hsawamur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# clang の方が良い
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = r
SRCS = ft_strlen.c \
		\
		ft_strdup.c \
		ft_substr.c \
		ft_strtrim.c \

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@ -I.

# $@ target名
$(NAME): $(SRCS:.c=.o)
	$(AR) $(ARFLAGS) $(NAME) $(SRCS:.c=.o)

all: 
	$(NAME)

clean: $(SRCS:.c=.o)
	rm $(SRCS:.c=.o)
 
fclean:
	make clean
	rm -f $(NAME)

re:
	make fclean
	make

.PHONY: all clean fclean re
