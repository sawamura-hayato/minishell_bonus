# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 17:16:20 by hsawamur          #+#    #+#              #
#    Updated: 2023/09/03 21:56:16 by tyamauch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g
# CFLAGS = -Wall -Wextra -Werror

RL_DIR = $(shell brew --prefix readline)
CFLAGS += -I$(READLINE_DIR)/include
RL_FLAGS = -L$(RL_DIR)/lib -lreadline

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/repl.c	\
		$(SRCS_DIR)/init.c

RM = rm -rf

TOKENIZE_DIR = tokenize
SRCS += $(SRCS_DIR)/$(TOKENIZE_DIR)/set_flag.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/linear_linked_token.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/get_current_token.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/get_current_word_size.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/get_type_word.c \
		$(SRCS_DIR)/$(TOKENIZE_DIR)/tokenize.c

 PARSE_DIR = parse
 SRCS += $(SRCS_DIR)/$(PARSE_DIR)/parse.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/ast_error.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/debug_print_ast.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/ast_expect.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/ast_command_list.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/ast_operator_node.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/command_word_list.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/command_redirect_list.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/redirect_set_type.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/free_parse.c \
 		$(SRCS_DIR)/$(PARSE_DIR)/token_utils.c

 HEREDOC_DIR = heredoc
 SRCS += $(SRCS_DIR)/$(HEREDOC_DIR)/heredoc.c \
 		$(SRCS_DIR)/$(HEREDOC_DIR)/heredoc_delete.c \
 		$(SRCS_DIR)/$(HEREDOC_DIR)/heredoc_read.c

EXPANSION_DIR = expansion
EXPANSION_FILENAME_DIR = expand_filename
EXPANSION_DELETE_QUOTE = expand_delete_quote

SRCS += $(SRCS_DIR)/$(EXPANSION_DIR)/expansion.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/expand_debug.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/expand_word_list.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/expand_redirect.c \

EXPANSION_VARI_DIR = expand_variable
SRCS += $(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_VARI_DIR)/expand_variable.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_VARI_DIR)/expand_dollar_quote_string_word.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_VARI_DIR)/expand_get_expanded_token.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_VARI_DIR)/expand_get_exit_status.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_VARI_DIR)/expand_get_str_to_dollar.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_VARI_DIR)/delete_word_list.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_VARI_DIR)/delete_redirect.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_VARI_DIR)/expand_is_abm_error.c \

EXPANSION_WORD_SPLIT_DIR = expand_word_splitting
SRCS += $(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_WORD_SPLIT_DIR)/expand_word_splitting.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_WORD_SPLIT_DIR)/expand_is_word_splitting.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_WORD_SPLIT_DIR)/new_word_list.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_WORD_SPLIT_DIR)/expand_redirect_list_word_splittitng.c \
		$(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_WORD_SPLIT_DIR)/expand_word_list_word_splitting.c \

EXPANSION_DELETE_QUOTE = expand_delete_quote
SRCS += $(SRCS_DIR)/$(EXPANSION_DIR)/$(EXPANSION_DELETE_QUOTE)/expand_delete_quote.c

EXEC_DIR = exec
SRCS += $(SRCS_DIR)/$(EXEC_DIR)/exec.c \
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_make_filepath.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_get_filepath.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_child_process.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_do_redirection.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_fork.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_pipe.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_wait_child_process.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_is_error.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_put_error.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_heredoc.c	\
	    $(SRCS_DIR)/$(EXEC_DIR)/exec_free.c

ENVS_DIR = $(SRCS_DIR)/envs
SRCS += $(ENVS_DIR)/envs_init.c	\
		$(ENVS_DIR)/envs_newnode.c	\
		$(ENVS_DIR)/envs_funcs.c	\
		$(ENVS_DIR)/envs_make_envp.c

BUILTIN_DIR = $(SRCS_DIR)/builtin
SRCS += $(BUILTIN_DIR)/builtin.c	\
	    $(BUILTIN_DIR)/export/export.c	\
	    $(BUILTIN_DIR)/export/export_show.c	\
	    $(BUILTIN_DIR)/export/export_add.c	\
	    $(BUILTIN_DIR)/export/export_is_error.c	\
	    $(BUILTIN_DIR)/export/export_error.c	\
	    $(BUILTIN_DIR)/export/export_set_oldpwd.c	\
	    $(BUILTIN_DIR)/pwd/pwd.c	\
	    $(BUILTIN_DIR)/echo/echo.c	\
	    $(BUILTIN_DIR)/exit/exit.c	\
 	    $(BUILTIN_DIR)/exit/exit_error.c	\
 	    $(BUILTIN_DIR)/exit/exit_overflow.c	\
 	    $(BUILTIN_DIR)/unset/unset.c	\
 	    $(BUILTIN_DIR)/env/env.c	\
 	    $(BUILTIN_DIR)/cd/cd.c	\
 	    $(BUILTIN_DIR)/cd/cd_cdpath.c	\
 	    $(BUILTIN_DIR)/cd/cd_error.c	\
 	    $(BUILTIN_DIR)/cd/cd_delete_dot.c	\
	    $(BUILTIN_DIR)/cd/cd_convert_path.c	\
	    $(BUILTIN_DIR)/cd/cd_delete_dot_slash.c	\
	    $(BUILTIN_DIR)/cd/cd_delete_dotdot.c	\
	    $(BUILTIN_DIR)/cd/cd_delete_dotdot_if_needed.c	\
	    $(BUILTIN_DIR)/cd/cd_delete_slash.c	\
	    $(BUILTIN_DIR)/cd/cd_replace_non_leading_consecutive_slashes.c	\
	    $(BUILTIN_DIR)/cd/cd_delete_leading_slashes.c	\
	    $(BUILTIN_DIR)/cd/cd_get_pre_comp.c	\
	    $(BUILTIN_DIR)/cd/cd_exec.c

SIGNAL_DIR = $(SRCS_DIR)/signal
SRCS +=	$(SIGNAL_DIR)/signal.c	\
		$(SIGNAL_DIR)/signal_readline.c	\
		$(SIGNAL_DIR)/signal_heredoc.c	\
		$(SIGNAL_DIR)/signal_exec.c	\
		$(SIGNAL_DIR)/eof.c

LIBRARY_DIR = library
LIBRARY_AFILE = $(LIBRARY_DIR)/library.a

OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBRARY_DIR)/$(INCLUDES_DIR) -I$(RL_DIR)/include

$(NAME): $(OBJS) $(LIBRARY_AFILE)
	$(CC) $(CFLAGS) -o $@ $^ $(RL_FLAGS)

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
