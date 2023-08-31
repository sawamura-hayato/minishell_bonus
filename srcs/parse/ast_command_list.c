/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:19:14 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/31 12:32:00 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_command	*command_list_init_node(void)
{
	t_command	*node;

	node = try_calloc(1, sizeof(t_command));
	node->fd = STDOUT_FILENO;
	node->pid = -1;
	return (node);
}

t_ast	*ast_command_node(t_token **current_token, t_data *d)
{
	t_ast	*ast_command_node;
	t_token	*token;

	ast_command_node = ast_init_node();
	token = *current_token;
	if (token == NULL)
	{
		ast_syntax_error(d, token);
		return (NULL);
	}
	ast_command_node->type = set_ast_node_type(token);
	if (ast_command_node->type != PS_COMMAND)
		ast_syntax_error(d, token);
	if (token->tk_type == TK_OPEN_PARENTHESIS
		|| token->tk_type == TK_CLOSE_PARENTHESIS)
		ast_syntax_error(d, token);
	return (ast_command_list(ast_command_node, current_token, d));
}

t_ast	*ast_command_list(t_ast *ast_command_node, t_token **current_token,
		t_data *d)
{
	t_token		*token;
	t_command	*command_list_node;
	bool		redirect_flag;

	token = *current_token;
	command_list_node = command_list_init_node();
	redirect_flag = false;
	ast_command_node->command_list = command_list_node;
	while (token != NULL && !ast_is_opereter(token->tk_type))
	{
		if (token_is_redirect(token->tk_type) || redirect_flag)
		{
			command_redirect_list(&(command_list_node->redirect_list),
				&token, d, redirect_flag);
			redirect_flag = !redirect_flag;
		}
		else
			command_word_list(&(command_list_node->word_list), &token, d);
		if (token_next(&token, d) == NULL || d->syntax_flag)
			break ;
		*current_token = token;
	}
	return (ast_command_node);
}
