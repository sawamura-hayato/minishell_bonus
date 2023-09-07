/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/07 18:07:45 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_ast	*ast_init_node(t_ast_node_type type)
{
	t_ast	*node;

	node = try_calloc(1, sizeof(t_ast));
	node->type = type;
	return (node);
}

t_ast_node_type	set_ast_node_type(t_token *token)
{
	t_ast_node_type	type;

	type = PS_COMMAND;
	if (token->tk_type == TK_PIPE)
		type = PS_PIPE;
	else if (token->tk_type == TK_LOGICAL_AND)
		type = PS_LOGICAL_AND;
	else if (token->tk_type == TK_LOGICAL_OR)
		type = PS_LOGICAL_OR;
	return (type);
}

t_ast	*ast_make_ast(t_token **current_token, t_data *d)
{
	t_token			*token;
	t_ast			*left_node;
	t_ast			*right_node;
	t_ast_node_type	type;

	token = *current_token;
	left_node = ast_command_node(&token, d);
	if (d->syntax_flag)
		return (ast_free_all_nodes(left_node));
	while (true)
	{
		if (token == NULL || !ast_is_opereter(token->tk_type))
			break ;
		type = set_ast_node_type(token);
		token_next(&token, d);
		right_node = ast_command_node(&token, d);
		if (d->syntax_flag)
			return (ast_free_right_left_nodes(left_node, right_node));
		left_node = ast_operator_node(type, left_node, right_node, d);
		if (d->syntax_flag)
			return (ast_free_all_nodes(left_node));
	}
	*current_token = token;
	return (left_node);
}

t_ast	*parse(t_token **current_token, t_data *d)
{
	t_ast	*ast;
	t_token	*token;

	ast = ast_make_ast(current_token, d);
	token = *current_token;
	if (!d->syntax_flag && token != NULL)
	{
		ast_syntax_error(d, token);
		ast = ast_free_all_nodes(ast);
	}
	return (ast);
}
