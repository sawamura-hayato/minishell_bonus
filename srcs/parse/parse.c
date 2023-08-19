/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/18 18:55:34 by tyamauch         ###   ########.fr       */
/* ************************************************************************** */

/*                                                                            */
#include "parse.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

t_ast	*parse(t_token **current_token, t_data *d)
{
	t_token			*token;
	t_ast			*left_node;
	t_ast			*right_node;
	t_ast_node_type	type;

	token = *current_token;
	left_node = ast_command_node(&token, d);
	printf("left node:%s\n",left_node->command_list->word_list->word);
	printf("left node p:%p\n",left_node);
	printf("token:%s\n",token->word);
	printf("current token:%s\n",(*current_token)->word);
	if (d->syntax_flag)
		return (left_node);
	while (true)
	{
		if (token != NULL && ast_is_opereter(token->type))
		{
			printf("token2:%s\n",token->word);
			printf("current token:%s\n",(*current_token)->word);
			type = PS_PIPE;
			token = token->next; //operatarのtoken
			printf("token2:%s\n",token->word);
			printf("current token:%s\n",(*current_token)->word);
			right_node = ast_command_node(&token,d);
			printf("right node:%s\n",right_node->command_list->word_list->word);
			printf("right node p:%p\n",right_node);
			if(d->syntax_flag)
				return (left_node);
			left_node = ast_operator_node(type, left_node,
					right_node,d);
			printf("ope node d:%d\n",left_node->type);
			printf("ope node p:%p\n",left_node);
			printf("ope node left:p:%p\n",left_node->left_hand);
			printf("ope node right:p:%p\n",left_node->right_hand);
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
	printf("token_next:%s\n",token->word);
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
	if(token->type == SINGLE_QUOTE)
		return (true);
	else if(token->type == DOUBLE_QUOTE)
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
