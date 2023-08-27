/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/27 19:40:16 by tyamauch         ###   ########.fr       */
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

t_ast	*parse(t_token **current_token, t_data *d)
{
	t_token			*token;
	t_ast			*left_node;
	t_ast			*right_node;
	t_ast_node_type	type;

	token = *current_token;
	left_node = ast_command_node(&token, d);
	if (d->syntax_flag)
	{
		ast_free_all_nodes(left_node);	
		return (NULL);
	}
	while (true)
	{	
		if (token != NULL && ast_is_opereter(token->tk_type))
		{	
			type = set_ast_node_type(token);
			if(token_next(&token,d) == NULL)
			{
				ast_syntax_error(d,token);
				ast_free_all_nodes(left_node);	
				return (NULL);
			}
			right_node = ast_command_node(&token,d);
			if(d->syntax_flag)
			{
				ast_free_all_nodes(left_node);	
				return (NULL);
			}
			left_node = ast_operator_node(type, left_node,
					right_node,d);
			if(d->syntax_flag)
			{
				ast_free_all_nodes(left_node);	
				return (NULL);
			}
		}
		else
		{
			return (left_node);
		}
	}
}
