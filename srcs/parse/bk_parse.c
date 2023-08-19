/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/17 20:06:12 by tyamauch         ###   ########.fr       */
/* ************************************************************************** */

/*                                                                            */
#include "parse.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

t_ast	*parse(t_token **current_token, t_data *d)
{
	const t_token			*token;
	t_ast			*left_node;
	t_ast			*right_node;
	t_ast_node_type	type;

	token = *current_token;
	/* left_node = ast_command_node(&token, d); */
	left_node = ast_command_node(current_token, d);
	printf("left node:%s\n",left_node->command_list->word_list->word);
	printf("left node p:%p\n",left_node);
	if (d->syntax_flag)
		return (left_node);
	printf("token:%s\n",token->word);
	printf("current_token:%s\n",(*current_token)->word);
	while (true)
	{
		if ((*current_token) != NULL && ast_is_opereter((*current_token)->type))
		{
			type = PS_PIPE;
			/* type = (*current_token)->type; */
			*current_token = (*current_token)->next;
			right_node = ast_command_node(current_token,d);
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

	token = *current_token;
	command_list_node = command_list_init_node();
	ast_command_node->command_list = command_list_node;
	while (token != NULL && !ast_is_opereter(token->type))
	{
		printf("token :%s\n",token->word);
		if (token_is_redirect(token->type))
			command_redirect_list(&(ast_command_node->command_list->redirect_list),current_token,d);
		else
		{
			command_word_list(&(ast_command_node->command_list->word_list),
								current_token);
		}
		if (token_next(current_token,d) == NULL || d->syntax_flag)
			break;
		token = token->next;
			/* return (NULL); */
	}
	return (ast_command_node);
}

t_ast	*ast_operator_node(t_ast_node_type type, t_ast *left_hand, t_ast *right_hand, t_data *d)
{
	t_ast	*ast_operator_node;

	if (right_hand == NULL)
	{
		ast_syntax_error(d);
		return (NULL); 
	}
	ast_operator_node = ast_init_node();
	//type_set();token typeからast typeに変換する関数
	ast_operator_node->type = type;
	ast_operator_node->left_hand = left_hand;
	ast_operator_node->right_hand = right_hand;
	return (ast_operator_node);
}

t_ast	*ast_init_node()
{
	t_ast	*node;

	node = try_calloc(1, sizeof(t_ast));
	return (node);
}

t_command *command_list_init_node()
{
	t_command* node;
	node = try_calloc(1, sizeof(t_command));
	node->fd = STDOUT_FILENO;
	node->pid = -1;

	return(node);
}

void	command_word_list(t_word_list **head, t_token **current_token)
{
	t_word_list	*word_node;
	t_token *token;

	token = *current_token;
	word_node = word_list_init_node(token);
	word_list_addback(head, word_node);
}

t_word_list	*word_list_init_node(t_token *token)
{
	t_word_list	*node;

	node = try_calloc(1, sizeof(t_word_list));
	node->word = try_strdup(token->word);
	node->index = token->index;
	node->type = token->type;
	return (node);
}

void			word_list_addback(t_word_list **head, t_word_list *new_node)
{
	t_word_list	*node;

	node = *head;
	while (node != NULL)
	{
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	if (node != NULL)
	{
		node->next = new_node;
		new_node->next = NULL;
	}
	else
	{
		new_node->next = NULL;
		*head = new_node;
	}
}

void	command_redirect_list(t_redirect_list **head,
							t_token **current_token,
							t_data *d)
{
	t_token		*token;
	t_redirect_list	*node;

	token = *current_token;
	node = redirect_init_node(token);
	redirect_list_addback(head, node);
	token = token->next;
	if (token == NULL || ast_is_opereter(token->type))
	{
		ast_syntax_error(d);
		return;
	}
	node = redirect_init_node(token);
	redirect_list_addback(head, node);
	token = token->next;
	if (token == NULL || ast_is_opereter(token->type))
	{
		ast_syntax_error(d);
		return;
	}
}

//redirectのnode(<)
t_redirect_list	*redirect_init_node(t_token *token)
{
	t_redirect_list *node;
	node = try_calloc(1, sizeof(t_redirect_list));
	//t_redirectとtokenをstrcmpなどで比較する必要がある
	redirect_set_type(node,token); //redirectタイプをsetする関数
	return (node);
}

void	redirect_set_type(t_redirect_list *node,t_token *token)
{
	if(token->word[0] == '<')
		node->type = PS_REDIRECTING_INPUT;
}

void	redirect_list_addback(t_redirect_list **head, t_redirect_list *new_node)
{
	t_redirect_list	*node;

	node = *head;
	while (node != NULL)
	{
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	if (node != NULL)
	{
		node->next = new_node;
		new_node->next = NULL;
	}
	else
	{
		new_node->next = NULL;
		*head = new_node;
	}
}

//token のindexを使う処理に変更するかも
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

/* void	ast_syntax_error(t_data *d) */
/* { */
/* 	printf("syntax_error"); */
/* 	d->exit_status = 2; */
/* 	d->syntax_flag = true; */
/* } */

void	ast_free_all_nodes(t_ast *node)
{
	if (node != NULL && node->left_hand != NULL)
		ast_free_all_nodes(node->left_hand);
	if (node != NULL && node->right_hand != NULL)
		ast_free_all_nodes(node->right_hand);
	free(node);
}

bool	ast_is_opereter(t_token_type type)
{
	if(type == LOGICAL_OR || type == LOGICAL_AND || type == PIPE)
		return(true);
	else
		return(false);
}

bool	token_is_redirect(t_token_type type)
{
	if(type == REDIRECT)
		return(true);
	else
		return(false);
}

/* void	ast_expect(t_token **current_token, char op,t_data *d) */
/* { */
/* 	t_token *token; */

/* 	token = *current_token; */
/* 	if (token->type != WORD || token->word[0] != op) */
/* 	{ */
/* 		ast_syntax_error(d); */
/* 		return; */
/* 	} */
/* 	token = token->next; */
/* } */
