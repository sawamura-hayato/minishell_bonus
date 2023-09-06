/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:19:14 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/06 18:38:57 by tterao           ###   ########.fr       */
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

	ast_command_node = ast_init_node();
	token = *current_token;
	node = NULL;
	if (token == NULL)
	{
		ast_syntax_error(d, token);
		return (ast_command_node);
	}
	if (token->tk_type == TK_OPEN_PARENTHESIS)
	{
		token = token->next;
		*current_token = token;
		node = parse(current_token, d);
		ast_expect(current_token, d);
		token = *current_token;
		// printf("token after expect: %s\n",token->word);
		if (token != NULL)
			token = token->next;
		*current_token = token;
		// printf("token %s\n",token->word);
		return (node);
	}
	return (ast_command_list(ast_command_node, current_token, d));
}

void	ast_expect_word(t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
if ((!d->syntax_flag) && (token == NULL || token->tk_type != WORD))
	{
		ast_syntax_error(d, token);
		*current_token = token->next;
		return ;
	}
}

t_ast	*ast_command_list(t_ast *ast_command_node, t_token **current_token,
		t_data *d)
{
	t_token		*token;
	t_command	*command_list_node;
	bool		redirect_flag;

	token = *current_token;
	ast_expect_word(current_token, d);
	command_list_node = command_list_init_node();
	redirect_flag = false;
	ast_command_node->command_list = command_list_node;
	while (token != NULL && !ast_is_opereter(token->tk_type) && !d->sigint_flag)
	{
		if (token_is_redirect(token->tk_type) || redirect_flag)
		{
			command_redirect_list(&(command_list_node->redirect_list),
				&token, d, redirect_flag);
			redirect_flag = !redirect_flag;
		}
		else if (token->tk_type == TK_CLOSE_PARENTHESIS && (token->next == NULL || ast_is_opereter(token->next->tk_type)))
			break ;
		else if (token->tk_type == TK_CLOSE_PARENTHESIS)
			d->syntax_flag = true;
		else
			command_word_list(&(command_list_node->word_list), &token, d);
		token = token->next;
	}
	// printf("command list token %s\n",token->word);
	*current_token = token;
	return (ast_command_node);
}
