/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/10 16:45:24 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_ast_list_type	set_ast_list_node_type(t_token_type tk_type)
{
	t_ast_list_type	ast_type;

	ast_type = AST_ROOT;
	if (tk_type == TK_LOGICAL_AND)
		ast_type = AST_LOGICAL_AND;
	else if (tk_type == TK_LOGICAL_OR)
		ast_type = AST_LOGICAL_OR;
	return (ast_type);
}

static t_ast_list	*ast_list_init_node(t_token *head, t_token **current_token)
{
	t_ast_list	*node;
	t_token		*token;

	token = *current_token;
	node = try_calloc(1, sizeof(t_ast_list));
	node->next = NULL;
	if (head == token)
		node->type = AST_ROOT;
	else if (token->tk_type == TK_LOGICAL_AND)
		node->type = AST_LOGICAL_AND;
	else if (token->tk_type == TK_LOGICAL_OR)
		node->type = AST_LOGICAL_OR;
	if (head != token)
		*current_token = token->next;
	return (node);
}

static void	ast_list_addback(t_ast_list **head, t_ast_list *new_node)
{
	t_ast_list	*node;

	node = *head;
	while (node != NULL)
	{
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	if (node != NULL)
	{
		node->next = new_node;
		new_node->next = NULL;
	}
	else
	{
		new_node->next = NULL;
		*head = new_node;
	}
}

t_ast_list	*parse(t_token *tk_head, t_data *d)
{
	t_token		*token;
	t_ast_list	*ast_head;
	t_ast_list	*list_node;

	token = tk_head;
	ast_head = NULL;
	while (token != NULL && !d->syntax_flag)
	{
		list_node = ast_list_init_node(tk_head, &token);
		list_node->ast = ast_make_ast(&token, d);
		ast_list_expect(&token, d);
		ast_list_addback(&ast_head, list_node);
	}
	if (d->syntax_flag == true)
		list_node = ast_free_ast_list(ast_head);
	return (ast_head);
}
