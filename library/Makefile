# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 13:32:50 by hsawamur          #+#    #+#              #
#    Updated: 2023/08/26 15:59:44 by hsawamur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = library.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address
AR = ar
ARFLAGS = -r
RM = rm -rf

SRCS_DIR = srcs

FT_DIR = ft
SRCS += $(SRCS_DIR)/$(FT_DIR)/ft_strlen.c \
			$(SRCS_DIR)/$(FT_DIR)/ft_substr.c \
			$(SRCS_DIR)/$(FT_DIR)/ft_strtrim.c \
			$(SRCS_DIR)/$(FT_DIR)/ft_is_operator.c \
			$(SRCS_DIR)/$(FT_DIR)/ft_is_special_char.c \
			$(SRCS_DIR)/$(FT_DIR)/ft_isspace.c \
			$(SRCS_DIR)/$(FT_DIR)/ft_islower.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_isupper.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_memchr.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_memset.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_strcmp.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_strncmp.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_strcmp_ignorecase.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_atoi.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_isdigit.c \
			$(SRCS_DIR)/$(FT_DIR)/ft_strchr.c \
			$(SRCS_DIR)/$(FT_DIR)/ft_atol.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_isdigit.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_strstr.c	\
			$(SRCS_DIR)/$(FT_DIR)/ft_strrchr.c

TRY_DIR = try
SRCS +=  $(SRCS_DIR)/$(TRY_DIR)/try_strdup.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_calloc.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_malloc.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_substr.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_strjoin.c	\
			$(SRCS_DIR)/$(TRY_DIR)/try_write.c	\
			$(SRCS_DIR)/$(TRY_DIR)/try_itoa.c	\
			$(SRCS_DIR)/$(TRY_DIR)/try_strjoin_free.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_dup.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_dup2.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_open.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_close.c \
			$(SRCS_DIR)/$(TRY_DIR)/try_strjoin_free.c	\
			$(SRCS_DIR)/$(TRY_DIR)/try_chdir.c	\
			$(SRCS_DIR)/$(TRY_DIR)/try_stat.c	\
			$(SRCS_DIR)/$(TRY_DIR)/try_pipe.c

# the writing below converts only operator using the pattern match(%) in this code.
# OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
# src/*.c->objs/src/*.o
OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR) -I../includes # 相対パスで指定しないほうがいい、解決方法を考える必要あり

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
