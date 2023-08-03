# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 13:32:50 by hsawamur          #+#    #+#              #
#    Updated: 2023/08/03 17:54:48 by hsawamur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
ARFLAGS = -r

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/ft_strlen.c \
			$(SRCS_DIR)/ft_strdup.c \
			$(SRCS_DIR)/ft_substr.c \
			$(SRCS_DIR)/ft_strtrim.c \
			$(SRCS_DIR)/ft_is_operator.c \
			$(SRCS_DIR)/ft_is_meta_char.c \
			$(SRCS_DIR)/ft_isspace.c \

# the writing below converts only operator using the pattern match(%) in this code.
# OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
# src/*.c->objs/src/*.o
OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) 
	$(AR) $(ARFLAGS) $@ $(OBJS)

all: $(NAME)

clean:
	$(RM) -r $(OBJS_DIR)
 
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
