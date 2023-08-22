/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/22 19:59:07 by tyamauch         ###   ########.fr       */
/* ************************************************************************** */

/*                                                                            */
#include "parse.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

static t_ast_node_type set_ast_node_type(t_token *token)
{
	t_ast_node_type type;
	if(token->type == TOKEN_PIPE)
		type = PS_PIPE;
	else if(TOKEN_LOGICAL_AND)
		type = PS_LOGICAL_AND;
	else if(TOKEN_LOGICAL_OR)
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
	/* printf("%s\n",left_node->command_list->word_list->word); */
	if (d->syntax_flag)
		return (left_node);
	while (true)
	{
		if (token != NULL && ast_is_opereter(token->type))
		{
			type = set_ast_node_type(token);
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

t_ast	*ast_init_node()
{
	t_ast	*node;

	node = try_calloc(1, sizeof(t_ast));
	return (node);
}

/* //token のindexを使う処理に変更するかも */
t_token	*token_next(t_token **current_token,t_data *d)
{
	t_token	*token;

	token = *current_token;
	if(token->next== NULL)
		return(NULL);
	token = token->next;
	if (token != NULL && token_is_quotation(token)) 
	{
		if(token_is_quotation_closed(token) == false)
		{
			ast_syntax_error(d);
			return (NULL);
		}
	}
	*current_token = token;
	return (*current_token);
}

bool token_is_quotation(t_token *token)
{
	if(token->type == TOKEN_SINGLE_QUOTE)
		return (true);
	else if(token->type == TOKEN_DOUBLE_QUOTE)
		return (true);
	else
		return(false);

}
bool					token_is_quotation_closed(t_token *token)
{
	if(token->word[0] == '"' || token->word[0] == '\'')
		return(true);
	else
		return(false);
}

void	ast_free_all_nodes(t_ast *node)
{
	if (node != NULL && node->left_hand != NULL)
		ast_free_all_nodes(node->left_hand);
	if (node != NULL && node->right_hand != NULL)
		ast_free_all_nodes(node->right_hand);
	free(node);
}

bool	token_is_redirect(t_token_type type)
{
	if(type == REDIRECT)
		return(true);
	else
		return(false);
}
