/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/22 13:13:51 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "tokenize.h"
#include "ft.h"
#include "init.h"

typedef enum e_redirect_type
{
	PS_REDIRECTING_INPUT,	  // <
	PS_REDIRECTING_OUTPUT,	  // >
	PS_APPENDING_OUTPUT,	  // >>
	PS_FILE,				  // redirect fil
	PS_HERE_DOCUMENTS,		  // <<
	PS_DELIMITER,			  // << delimitter(クウォートがない場合)
	PS_QUOTE_DELIMITER,		  // << delimitter(クウォートがある場合)
	PS_REDIRECT_SINGLE_QUOTE, // < 'file'
	PS_REDIRECT_DOUBLE_QUOTE  // < "file" < <- " <- file <- "
} t_redirect_list_type;

typedef enum e_ast_node_type
{
	PS_PIPE,
	PS_LOGICAL_AND,
	PS_LOGICAL_OR,
	PS_COMMAND,
} t_ast_node_type;

typedef struct s_word_list
{
	char *word;
	size_t index; // クォートが閉じるまで更新されない
	t_token_type type;
	struct s_word_list *next;
} t_word_list;

typedef struct s_redirect_list
{
	char *word;
	size_t index;
	t_redirect_list_type type;
	bool is_ambiguous_error;	  // 初期値はfalse
	struct s_word_split *ws_node; // NEW!
	struct s_redirect *next;
} t_redirect_list_list;

typedef struct s_command
{
	t_word_list *word_list;
	t_redirect_list_list *redirect_list;
	int fd;	   // どこにコマンドを出力するか(初期値はSTD OUT FILNE NO)
	pid_t pid; // 子プロセスのIDを管理(初期値は-1)
} t_command;

typedef struct s_ast
{
	t_ast_node_type type;
	struct s_command *command_list;
	struct s_ast *left_hand;
	struct s_ast *right_hand;
} t_ast;

// t_ast関連
t_ast *parse(t_token **current_token, t_data *d);
t_ast *ast_command_node(t_token **current_token, t_data *d);
t_ast *ast_command_list(t_ast *ast_command_node, t_token **current_token, t_data *d);
t_ast *ast_operator_node(t_ast_node_type type, t_ast *left_hand,
						 t_ast *right_hand, t_data *d);
t_ast *ast_init_node();
void ast_addback(t_ast **head, t_ast *new_node);
void ast_free_all_nodes(t_ast *node);

// t_command関連
void command_word_list(t_word_list **word_list,
					   t_token **current_token);
void command_redirect_list(t_redirect_list_list **redirect_list,
						   t_token **current_token,
						   t_data *d);
bool token_is_redirect(t_token type);

// t_word_list関連
t_word_list *word_list_init_node(t_token *token);
void *word_list_addback(t_word_list **head, t_word_list *node);

// t_redirect_list関連
t_redirect_list_list *redirect_init_node(t_token *token);
void *redirect_list_addback(t_redirect_list_list **head,
							t_redirect_list_list *node);

void redirect_set_type(t_redirect_list_list *node, t_token *token); // redirectタイプをsetする関数
// error関連
bool ast_is_operator(t_token_type type);
bool token_is_quotation_closed(t_token *token);
void ast_expect(t_token **current_token, char op, t_data *d);
t_token *token_next(t_token **current_token, t_data *d);
void ast_syntax_error(t_data *d);

/* void* try_calloc(size_t nmemb,size_t size); */
#endif
