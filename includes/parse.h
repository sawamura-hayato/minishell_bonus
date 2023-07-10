/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/10 21:44:50 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

enum e_redirect_type
{
	REDIRECTING_INPUT, // <
	REDIRECTING_OUTPUT,// >
	APPENDING_OUTPUT,// >>
	FILE,// redirect file
	HERE_DOCUMENTS, // <<
	DELIMITER, // << delimitter
};

enum e_ast_type
{
	PIPE,
	LOGICAL_AND,
	LOGICAL_OR,
	COMMAND,
};

typedef struct s_word
{
    char                *word;
    struct s_word_list    *next;
}t_word;  

typedef struct s_redirect
{
	char				*word;
	struct s_redirect	*next;
	e_redirect_type		type;
}t_redirect;

typedef struct s_command
{
	t_word *word_list;
	t_redirect *t_redirect_list;
	int fd;
	pid_t pid;
}t_command;

typedef struct s_ast
{
	e_ast_type		type;
	struct t_command *command_list;
	struct s_ast	*left_hand;
	struct s_ast	*right_hand;
}	t_ast;


t_ast *ast_parse(t_token **token_adress);
t_ast *ast_command(t_token *token);
bool is_operator(e_ast_type type);
t_ast *ast_make_ast_ope(e_ast_type,t_ast *left_hand,t_ast *right_hand);

void* try_malloc(size_t size);
void ast_expect(t_token **token,char op); 
void ast_make_command_list(t_ast *node,t_token **token);

void ast_make_redirect_list(t_redirect redirect_list, t_token **token_address);
t_ast *ast_init_redirect_node(t_redirect *node);
void *ast_add_back_redirect_list(t_redirect **head,t_redirect *node);

void ast_make_word_list(t_command command_list, t_token token);
t_ast *ast_init_word_node(t_word *word);
void *ast_add_back_word_list(t_word **head,t_word *node);

t_ast *ast_init_node(t_token **token_adress)
void ast_add_node(t_ast **head, t_ast *new_node);

t_token	*ast_token_next(t_token **token_address);
bool is_quotation_closed(t_token *token_adress);
void ast_free_all_nodes(t_ast *node);
void * syntax_error(t_ast *left_node,t_ast *right_node)

#endif
