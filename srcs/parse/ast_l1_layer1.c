/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_l1_layer1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:54:28 by tterao            #+#    #+#             */
/*   Updated: 2023/09/11 16:26:11 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	ast_l1_is_logical_operator(t_token *token)
{
	return (
		token->tk_type == TK_LOGICAL_AND || token->tk_type == TK_LOGICAL_OR
	);
}

t_ast_l1_type	ast_l1_set_node_type(t_token *token)
{
	t_ast_l1_type	type;

	type = AST_COMMAND;
	if (token->tk_type == TK_LOGICAL_AND)
		type = AST_LOGICAL_AND;
	else if (token->tk_type == TK_LOGICAL_OR)
		type = AST_LOGICAL_OR;
	return (type);
}

static t_ast_l1	*ast_l1_init(t_ast_l1_type type)
{
	t_ast_l1	*newnode;

	newnode = try_calloc(1, sizeof(t_ast_l1));
	newnode->type = type;
	return (newnode);
}

t_ast_l1	*ast_l1_operator_node(t_ast_l1_type type, t_ast_l1 *left,
			t_ast_l1 *right, t_data *d)
{
	t_ast_l1	*newnode;

	if (right == NULL || d->syntax_flag)
	{
		ast_l1_free(left);
		ast_l1_free(right);
		ast_syntax_error(d, NULL);
		return (NULL);
	}
	newnode = ast_l1_init(type);
	newnode->left_hand = left;
	newnode->right_hand = right;
	return (newnode);
}

t_ast_l1	*ast_l1_node(t_token **current_token, t_data *d)
{
	t_ast_l1	*newnode;
	t_token		*token;

	token = *current_token;
	if (token == NULL)
	{
		ast_syntax_error(d, token);
		return (NULL);
	}
	if (token->tk_type == TK_OPEN_PARENTHESIS)
	{
		token = token->next;
		newnode = ast_l1_layer1(&token, d);
		ast_expect(TK_CLOSE_PARENTHESIS, &token, d);
		if (token != NULL)
			token = token->next;
		*current_token = token;
		return (newnode);
	}
	newnode = ast_l1_init(AST_COMMAND);
	newnode->ast = ast_layer2(&token, d);
	*current_token = token;
	return (newnode);
}
