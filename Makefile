# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tterao <tterao@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 11:01:17 by hsawamur          #+#    #+#              #
#    Updated: 2023/08/15 21:22:09 by tyamauch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address

RL_DIR = $(shell brew --prefix readline)
RL_FLAGS = -L$(RL_DIR)/lib -lreadline

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/repl.c

RM = rm -rf

TOKENIZE_DIR = tokenize
SRCS += $(SRCS_DIR)/$(TOKENIZE_DIR)/set_flag.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/linear_linked_token.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/get_quote_token.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/get_current_token.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/get_current_word_size.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/get_next_token_index.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/tokenize.c

PARSE_DIR = parse
SRCS += $(SRCS_DIR)/$(PARSE_DIR)/parse.c \
		$(SRCS_DIR)/$(PARSE_DIR)/ast_error.c \
		$(SRCS_DIR)/$(PARSE_DIR)/ast_expect.c \

# ENVS_DIR = $(SRCS_DIR)/envs
# SRCS += $(ENVS_DIR)/init.c	\
# 		$(ENVS_DIR)/envs_newnode.c	\
# 		$(ENVS_DIR)/envs_funcs.c	\
		$(ENVS_DIR)/envs_make_envp.c

# BUILTIN_DIR = $(SRCS_DIR)/builtin
# SRCS += $(BUILTIN_DIR)/export/export.c	\
# 	    $(BUILTIN_DIR)/export/export_show.c	\
# 	    $(BUILTIN_DIR)/export/export_add.c	\
# 	    $(BUILTIN_DIR)/export/export_is_error.c	\
# 	    $(BUILTIN_DIR)/export/export_error.c


LIBRARY_DIR = library
LIBRARY_AFILE = $(LIBRARY_DIR)/library.a

OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBRARY_DIR)/$(INCLUDES_DIR) -I$(RL_DIR)/include

$(NAME): $(OBJS) $(LIBRARY_AFILE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY_AFILE) -o $(NAME) $(RL_FLAGS)
	# $(CC) $(CFLAGS) $(OBJS) -o $@ $^ $(RL_FLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBRARY_AFILE):
	$(MAKE) -C $(LIBRARY_DIR)

all: $(NAME)

clean:
	$(RM) $(OBJS_DIR) $(LIBRARY_DIR)/$(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBRARY_AFILE)

re: fclean all

.PHONY: all clean fclean re
