/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/10 12:28:48 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_ast_list_type	set_ast_list_node_type(t_token_type tk_type)
{
	t_ast_list_type ast_type;

	ast_type = AST_ROOT;
	if (tk_type == TK_LOGICAL_AND)
		ast_type = AST_LOGICAL_AND;
	else if (tk_type == TK_LOGICAL_OR)
		ast_type = AST_LOGICAL_OR;
	return (ast_type);
}

static t_ast_list	*ast_list_init_node(t_token_type tk_type)
{
	t_ast_list	*node;

	node = try_calloc(1, sizeof(t_ast_list));
	node->type = set_ast_list_node_type(tk_type);
	return (node);
}

static void	ast_list_addback(t_ast_list **head,
		t_ast_list *new_node)
{
	t_ast_list	*node;

	if(*head != NULL)
		node = *head;
	else
		node = NULL;
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
/* expect(); */

/* t_ast	*parse(t_token **current_token, t_data *d) */
t_ast_list	*parse(t_token **current_token, t_data *d)
{
	t_ast	*ast;
	t_token	*token;
	t_ast_list **head;
	t_ast_list *list_node;

	token = *current_token;
	while(token)
	{
		if(token != *current_token)
			ast_list_expect(&token,d);
		else
			*head = ast_list_init_node(token->tk_type);
		if(d->syntax_flag)
			break;
		list_node = ast_list_init_node(token->tk_type);
		list_node->ast = ast_make_ast(&token, d);
		ast_list_addback(head,list_node);
	}
	/* if (token != NULL || expext()) */
	if (token != NULL )
	{
		ast_syntax_error(d, token);
		ast = ast_free_all_nodes(ast);
	}
	return (*head);
}
