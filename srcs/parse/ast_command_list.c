/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:19:14 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/07 21:00:55 by tyamauch         ###   ########.fr       */
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
	t_ast	*node;
	t_token	*token;

	token = *current_token;
	if (token == NULL)
	{
		ast_syntax_error(d, token);
		return (NULL);
	}
	if (token->tk_type == TK_OPEN_PARENTHESIS)
	{
		token = token->next;
		node = ast_make_ast(&token, d);
		ast_expect(TK_CLOSE_PARENTHESIS, &token, d);
		if (token != NULL)
			token = token->next;
		*current_token = token;
		return (node);
	}
	ast_command_node = ast_init_node(PS_COMMAND);
	ast_expect(WORD, current_token, d);
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
	while (token != NULL && !ast_is_opereter(token->tk_type) && !d->syntax_flag
		&& token->tk_type != TK_CLOSE_PARENTHESIS)
	{
		if (token_is_redirect(token->tk_type) || redirect_flag)
		{
			command_redirect_list(&(command_list_node->redirect_list),
				&token, d, redirect_flag);
			redirect_flag = !redirect_flag;
		}
		else if (token->tk_type == TK_OPEN_PARENTHESIS)
			ast_syntax_error(d, token->next);
		else
			command_word_list(&(command_list_node->word_list), &token, d);
		token = token->next;
	}
	*current_token = token;
	return (ast_command_node);
}
