/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/28 23:03:26 by tyamauch         ###   ########.fr       */
/*   Updated: 2023/08/26 00:18:53 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

t_ast	*ast_init_node(void)
{
	t_ast	*node;

	node = try_calloc(1, sizeof(t_ast));
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

t_ast	*parse(t_token **current_token, t_data *d)
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
		/* if(token_next(&token, d) == NULL || d->syntax_flag) */
       /* return (ast_free_all_nodes(left_node)); */
		token_next(&token, d);
		right_node = ast_command_node(&token, d);
		if (d->syntax_flag)
		{
			printf("test\n");
			/* ast_free_node(right_node); */
			word_list_free(right_node->command_list->word_list);
			redirect_list_free(right_node->command_list->redirect_list);
			free(right_node->command_list);
			free(right_node);
			return (ast_free_all_nodes(left_node));
		}
		left_node = ast_operator_node(type, left_node, right_node, d);
		if (d->syntax_flag)
			return (ast_free_all_nodes(left_node));
	}
	return (left_node);
}
