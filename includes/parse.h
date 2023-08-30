/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/30 18:38:56 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "ft.h"
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
}							t_command;

typedef struct s_ast
{
	t_ast_node_type			type;
	struct s_command		*command_list;
	struct s_ast			*left_hand;
	struct s_ast			*right_hand;
}							t_ast;

// t_ast関連
t_ast						*parse(t_token **current_token, t_data *d);
t_ast						*ast_command_node(t_token **current_token,
								t_data *d);
t_ast						*ast_command_list(t_ast *ast_command_node,
								t_token **current_token, t_data *d);
t_ast						*ast_operator_node(t_ast_node_type type,
								t_ast *left_hand, t_ast *right_hand, t_data *d);
t_ast						*ast_init_node(void);
void						ast_addback(t_ast **head, t_ast *new_node);
void						*ast_free_all_nodes(t_ast *node);

void						debug_print_ast(t_ast *node);
// t_command関連
void						command_word_list(t_word_list **word_list,
								t_token **current_token, t_data *d);
void						command_redirect_list(t_redirect_list 
								**redirect_list,
								t_token **current_token, t_data *d,
								bool redirect_flag);
bool						token_is_redirect(t_token_type type);

void						redirect_set_type(t_redirect_list **head,
								t_redirect_list *node, t_token *token);
void						redirect_set_type_word(t_redirect_list *last_node,
								t_redirect_list *node, t_token *token);
t_redirect_list				*redirect_list_get_last_node(t_redirect_list 
								**head);
bool						is_redirect_operator(t_redirect_list *node);

// error関連
bool						ast_is_opereter(t_token_type type);
bool						token_is_quotation(t_token *token);

bool						token_is_quotation_closed(t_token *token);
void						ast_expect(t_token **current_token,
								t_data *d);
t_token						*token_next(t_token **current_token, t_data *d);
void						ast_syntax_error(t_data *d, t_token *token);
t_ast_node_type				set_ast_node_type(t_token *token);
void						*ast_free_node(t_ast *node);
void						*ast_free_right_left_nodes(t_ast *left_node,
								t_ast *right_node);
/* ls infileC a b */
/* | ls */

/* 		ls infile a b */
/* 		<< eof<Makefile> out */
/* 	>> apend */
/* | ls a b c d */

/* 	1 ls 2 infile 3 > 4a 5b 6 << 7eof < */
/* 	Makefile */
/* | ls 1ls 2infile 5b 3 > 4a << eof < Makefile */

/* 	cat infiile */
/* | */
/* ls */

/* -- ---------------------- */

/* cmd1 */
/* | cmd2 */
/* || cmd3 | cmd4 */

/* 	| */
/* || cmd4 | cmd3 cmd1 cmd2-- ---------------------- */

/* 	cmd1 */
/* 	| (cmd2 || cmd3) | cmd4 */

/* 	| cmd1 | */
/* || cmd4 cmd2 cmd3-- ---------------------- */

/* ------------------------(a || b) && */
/* ls */

/* && */
/* || ls a b-- ---------------------- */

/* | | command4 | comamnd3 command1 command2 */

/* | comamnd3 command1 command2 */

/* | command1 command2 */

/* 	< infile */

/* | command1 command2 comamnd3 command4 */
#endif
