/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/10 20:49:48 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_ast_l1	*ast_l1_layer1(t_token **current_token, t_data *d)
{
	t_token			*token;
	t_ast_l1		*left_node;
	t_ast_l1		*right_node;
	t_ast_l1_type	type;

	token = *current_token;
	left_node = ast_l1_node(&token, d);
	if (d->syntax_flag)
		return (ast_free_ast_l1(left_node));
	while (true)
	{
		if (token == NULL || !ast_l1_is_logical_operator(token))
			break ;
		type = ast_l1_set_node_type(token);
		token_next(&token, d);
		right_node = ast_l1_node(&token, d);
		left_node = ast_l1_operator_node(type, left_node, right_node, d);
		if (d->syntax_flag)
			return (ast_free_ast_l1(left_node));
	}
	*current_token = token;
	return (left_node);
}

t_ast_l1	*parse(t_token *tk_head, t_data *d)
{
	t_token		*token;
	t_ast_l1	*ast_l1;

	token = tk_head;
	ast_l1 = ast_l1_layer1(&token, d);
	if (token != NULL)
	{
		ast_syntax_error(d, token);
		ast_l1 = ast_free_ast_l1(ast_l1);
	}
	return (ast_l1);
}
