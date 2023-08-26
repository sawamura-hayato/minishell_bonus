/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/26 22:48:59 by tyamauch         ###   ########.fr       */
/*   Updated: 2023/08/26 00:18:53 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_ast	*ast_init_node()
{
	t_ast	*node;

	node = try_calloc(1, sizeof(t_ast));
	return (node);
}

t_ast_node_type set_ast_node_type(t_token *token)
{
	t_ast_node_type type;

	type = PS_COMMAND;
	if(token->tk_type == TK_PIPE)
		type = PS_PIPE;
	else if(token->tk_type == TK_LOGICAL_AND)
		type = PS_LOGICAL_AND;
	else if(token->tk_type == TK_LOGICAL_OR)
		type = PS_LOGICAL_OR;
	return(type);
}

static void free_list(t_ast *node)
{
	t_word_list * word_head;
	t_word_list * word_p;
	t_redirect_list * redirect_head;
	t_redirect_list * redirect_p;

	if(node->type != PS_COMMAND)
		free(node);
	else
	{
		word_head = node->command_list->word_list;
		word_p = word_head;
		redirect_head = node->command_list->redirect_list;
		redirect_p = redirect_head;
		while(word_p)
		{
			word_p = word_head->next;
			free(word_head);
		}
		while(redirect_p)
		{
			redirect_p = redirect_head->next;
			free(redirect_head);
		}
	}
}

void	ast_free_all_nodes(t_ast *node)
{
	if (node != NULL && node->left_hand != NULL)
		ast_free_all_nodes(node->left_hand);
	if (node != NULL && node->right_hand != NULL)
		ast_free_all_nodes(node->right_hand);
	free_list(node);
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
		return (left_node);
	while (true)
	{	
		if (token != NULL && ast_is_opereter(token->tk_type))
		{	
			type = set_ast_node_type(token);
			if(token_next(&token,d))
			{
				ast_syntax_error(d,token);
				return (left_node);
			}
			right_node = ast_command_node(&token,d);
			if(d->syntax_flag)
				return (left_node);
			left_node = ast_operator_node(type, left_node,
					right_node,d);
			if(d->syntax_flag)
				return (left_node);
		}
		else
		{
			return (left_node);
		}
	}
}
