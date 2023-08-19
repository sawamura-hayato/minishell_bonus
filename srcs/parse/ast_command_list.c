#include "parse.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

static t_command *command_list_init_node()
{
	t_command* node;
	node = try_calloc(1, sizeof(t_command));
	node->fd = STDOUT_FILENO;
	node->pid = -1;

	return(node);
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
		node = parse(current_token, d);
		ast_expect(current_token, ')',d);
		return (node);
	}
	if (token == NULL || ast_is_opereter(token->type))
	{
		ast_syntax_error(d);
		return(NULL);
	}
	return (ast_command_list(ast_command_node, current_token,d));
}

t_ast	*ast_command_list(t_ast *ast_command_node, t_token **current_token,t_data *d)
{
	t_token *token;
	t_command *command_list_node;
	bool redirect_flag;

	token = *current_token;
	command_list_node = command_list_init_node();
	redirect_flag = false;
	ast_command_node->command_list = command_list_node;
	while (token != NULL && !ast_is_opereter(token->type))
	{
		if (token_is_redirect(token->type) || redirect_flag)
		{
			command_redirect_list(&(ast_command_node->command_list->redirect_list),&token,d,redirect_flag);
			if(redirect_flag == false)
				redirect_flag = true;
			else
				redirect_flag = false;
		}
		else
		{
			command_word_list(&(ast_command_node->command_list->word_list),
								&token);
		}
		if (token_next(&token,d) == NULL || d->syntax_flag )
				break;
		/* printf("token is1:%s\n",token->word); */
		/* token_next(&token,d); */ 
	}
	return (ast_command_node);
}

