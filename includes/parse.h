/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/30 22:33:35 by tyamauch         ###   ########.fr       */
/*                                                +#+#+#+#+#+   +#+           */
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
	QUOTED_DELIMITER, // << delimitter
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
	t_command		*command_list;// cat infile
	t_redirect		*redirect_list;//<< eof < Makefile
	struct s_ast	*left_hand;
	struct s_ast	*right_hand;
}	t_ast;

void make_linked_list(t_ast *node,t_token **token);
void make_redirect_list(t_redirect redirect_list, t_token token);
void make_command_list(t_command, command_list, t_token token);
t_ast *ast_make_ast_comand(t_token **token_adress);
void ast_add_command_node(t_ast **head, t_ast *new_node);
t_ast * ast_make_ast_ope(e_ast_type type,t_ast *left_hand,t_ast *right_hand );
t_ast *ast_parse(t_token **token_adress); 
void expect(t_token **token,char op); 
t_ast *command(t_token **token); 

#endif
