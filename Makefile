# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 11:01:17 by hsawamur          #+#    #+#              #
#    Updated: 2023/08/03 15:47:55 by hsawamur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RL_DIR = $(shell brew --prefix readline)
RL_FLAGS = -L$(RL_DIR)/lib -lreadline

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/repl.c

TOKENIZE_DIR = tokenize
SRCS += $(SRCS_DIR)/$(TOKENIZE_DIR)/create_token.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/set_flag.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/get_quote_token.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/tokenize.c

PARSE_DIR = parse

LIBFT_DIR = libft
LIBFT_AFILE = $(LIBFT_DIR)/libft.a

OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/$(INCLUDES_DIR) -I$(RL_DIR)/include

$(NAME): $(OBJS) $(LIBFT_AFILE)
	$(CC) $(CFLAGS) -o $@ $^ $(RL_FLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_AFILE):
	$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	$(RM) -r $(OBJS_DIR) $(LIBFT_DIR)/$(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT_AFILE)

re: fclean all

.PHONY: all clean fclean re

