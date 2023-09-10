/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/10 20:41:39 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "init.h"
# include "library.h"
# include "tokenize.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# define SYNTAX_ERROR 2

typedef enum e_redirect_type
{
	PS_REDIRECTING_INPUT,
	PS_REDIRECTING_OUTPUT,
	PS_APPENDING_OUTPUT,
	PS_FILE,
	PS_HERE_DOCUMENTS,
	PS_DELIMITER,
	PS_QUOTE_DELIMITER,
}							t_redirect_type;

typedef enum e_ast_node_type
{
	PS_PIPE,
	PS_LOGICAL_AND,
	PS_LOGICAL_OR,
	PS_COMMAND,
}							t_ast_node_type;

typedef enum e_ast_list_type
{
	AST_COMMAND,
	AST_LOGICAL_AND,
	AST_LOGICAL_OR,
}							t_ast_l1_type;

typedef struct s_word_list
{
	char					*word;
	char					*type;
	t_token_type			tk_type;
	struct s_word_list		*next;
}							t_word_list;

typedef struct s_redirect_list
{
	char					*word;
	char					*type;
	t_redirect_type			re_type;
	bool					is_ambiguous_error;
	struct s_redirect_list	*next;
}							t_redirect_list;

typedef struct s_command
{
	t_word_list				*word_list;
	t_redirect_list			*redirect_list;
	int						fd;
	pid_t					pid;
	bool					redirect_success;
}							t_command;

typedef struct s_ast
{
	t_ast_node_type			type;
	struct s_command		*command_list;
	struct s_ast			*left_hand;
	struct s_ast			*right_hand;
}							t_ast;

typedef struct s_ast_l1
{
	t_ast				*ast;
	t_ast_l1_type		type;
	struct s_ast_l1		*left_hand;
	struct s_ast_l1		*right_hand;
}							t_ast_l1;

// t_ast関連
t_ast_l1		*parse(t_token *tk_head, t_data *d);
t_ast			*ast_layer2(t_token **current_token, t_data *d);
t_ast			*ast_command_node(t_token **current_token, t_data *d);
t_ast			*ast_command_list(t_ast *ast_command_node,
					t_token **current_token, t_data *d);
t_ast			*ast_operator_node(t_ast_node_type type, t_ast *left_hand,
					t_ast *right_hand, t_data *d);
t_ast			*ast_init_node(t_ast_node_type type);
void			ast_addback(t_ast **head, t_ast *new_node);
void			*ast_free_all_nodes(t_ast *node);
void			debug_print_ast(t_ast *node);

// t_ast_l1
t_ast_l1		*ast_l1_layer1(t_token **current_token, t_data *d);
t_ast_l1		*ast_l1_node(t_token **current_token, t_data *d);
t_ast_l1		*ast_l1_operator_node(t_ast_l1_type type, t_ast_l1 *left,
					t_ast_l1 *right, t_data *d);
t_ast_l1_type	ast_l1_set_node_type(t_token *token);
bool			ast_l1_is_logical_operator(t_token *token);

// t_command関連
void			command_word_list(t_word_list **word_list,
					t_token **current_token, t_data *d);
void			command_redirect_list(t_redirect_list **redirect_list,
					t_token **current_token, t_data *d,
					bool redirect_flag);
bool			token_is_redirect(t_token_type type);

void			redirect_set_type(t_redirect_list **head,
					t_redirect_list *node, t_token *token);
void			redirect_set_type_word(t_redirect_list *last_node,
					t_redirect_list *node, t_token *token);
t_redirect_list	*redirect_list_get_last_node(t_redirect_list **head);
bool			is_redirect_operator(t_redirect_list *node);

// error関連
bool			ast_is_opereter(t_token_type type);
bool			token_is_quotation(t_token *token);

bool			token_is_quotation_closed(t_token *token);
bool			token_is_parentheis(t_token *token);
void			ast_expect(t_token_type expecting_type,
					t_token **current_token, t_data *d);
void			ast_expect_word(t_token **current_token,
					t_data *d);
void			ast_list_expect(t_token **current_token,
					t_data *d);
t_token			*token_next(t_token **current_token, t_data *d);
void			ast_syntax_error(t_data *d, t_token *token);
t_ast_node_type	set_ast_node_type(t_token *token);
void			*ast_free_ast_l1(t_ast_l1 *node);
void			*ast_free_node(t_ast *node);
void			*ast_free_right_left_nodes(t_ast *left_node,
					t_ast *right_node);
void			debug_print_ast(t_ast *node);
void			debug_print_ast_l1(t_ast_l1 *node);

#endif
