#include "../../includes/parse.h"
#include <stdio.h>

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
		if (token != NULL && ast_is_operator(token->type))
		{
			/* type = token->type; */
			type = PS_COMMAND;
			token = token->next; //operatarのtoken
			right_node = ast_command_node(&token,d);
			if(d->syntax_flag)
				return (left_node);
			left_node = ast_operator_node(type, left_node,
					right_node,d);
			if(d->syntax_flag)
				return (left_node);
		}
		else
			return (left_node);
	}
}

t_ast	*ast_command_node(t_token **current_token, t_data *d)
{
	t_ast	*ast_command_node;
	t_token	*token;
	t_ast	*node;

	ast_command_node = ast_init_node();
	ast_command_node->type = PS_COMMAND;
	token = *current_token;
	if (token->word[0] == '(')
	{
		printf("test0:\n");
		node = parse(current_token, d);
		expect(current_token, ')',d);
		return (node);
	}
	if (token == NULL || ast_is_opereter(token->type))
	{
		printf("test1:\n");
		ast_syntax_error(d);
		return(NULL);
	}
	return (ast_command_list(ast_command_node, current_token,d));
}

t_ast	*ast_command_list(t_ast *ast_command_node, t_token **current_token,t_data *d)
{
	token = *current_token;
	while (token != NULL && !ast_is_opereter(token->type))
	{
		ast_command_node->command_list->fd = STDOUT_FINENO;
		ast_command_node->command_list->pid = -1;
		if (token_is_redirect(token->type))
			command_redirect_list(&(command_node->command_list->redirect_list,d),
									&token);
		else
			command_word_list(&(command_node->command_list->word_list),
								&token);
		if (!token_next(&token,d) || d->syntax_flag)
			return (NULL);
	}
	return (command_node);
}

void	ast_expect(t_token **current_token, char op,t_data *d)
{
	t_token *token;

	token = *current_token;
	if (token->kind != WORD || token->word[0] != op)
	{
		syntax_error(d);
		return
	}
	token = token->next;
}
