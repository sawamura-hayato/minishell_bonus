/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/15 20:42:00 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

enum e_redirect_type
{
	REDIRECTING_INPUT,
	REDIRECTING_OUTPUT,
	APPENDING_OUTPUT,
	FILE,
	HERE_DOCUMENTS,
	DELIMITER,
};

enum e_ast_type
{
	PIPE,
	LOGICAL_AND,
	LOGICAL_OR,
	COMMAND,
};

typedef struct s_command
{
	char				*word;
	struct s_command	*next;
}	t_command;

typedef struct s_redirect
{
	char				*word;
	struct s_redirect	*next;
	e_redirect_type		type;
}	t_redirect;

typedef struct s_ast
{
	e_ast_type		type;
	t_command		*command_list;
	t_redirect		*redirect_list;
	struct s_ast	*left_hand;
	struct s_ast	*right_hand;
}	t_ast;


bool		is_syntax_error(t_token *token);
bool		is_quotation_closed(t_token *token);
t_ast		*ast_new_node(e_ast_type type, t_ast *left_hand, t_ast *right_hand);
t_ast		*ast_new_node_command(t_command *command, t_redirect *redirect);
t_token		*consume(t_node *token);
t_command	*make_command_list(t_token *token);
t_command	*make_redirect_list(t_token *token);


#endif
