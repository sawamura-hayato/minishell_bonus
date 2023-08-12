/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/12 03:31:32 by tyamauch         ###   ########.fr       */
/* ************************************************************************** */

/*                                                                            */
#include "parse.h"
#include "tokenize.h"

t_ast	*parse(t_token **current_token, t_data *d)
{
	t_token			*token;
	t_ast			*left_node;
	t_ast_node_type	type;

	token = *current_token;
	left_node = ast_command_node(token, d);
	if (left_node == null)
		ast_free_all_nodes(left_node);
	while (true)
	{
		if (token != null && ast_is_operator(token->type))
		{
			type = token->type;
			token = token->next; //operatarのtoken
			left_node = ast_operator_node(type, left_node,
					ast_command_node(token, d));
			token = token->next; //
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
	ast_command_node->type = COMMAND;
	token = *current_token;
	if (token->word[0] == '(')
	{
		node = parse(current_token, d);
		expect(*token, ')');
		return (node);
	}
	if (token == null || ast_is_opereter(token->type))
		ast_syntax_error(d);
	return (ast_command_list(ast_command_node, current_token));
}

t_ast	*ast_command_list(t_ast *ast_command_node, t_token **current_token)
{
	token = *current_token;
	while (token != NULL && !ast_is_opereter(token->type))
	{
		ast_command_node->command_list->fd = STDOUT_FINENO;
		ast_command_node->command_list->pid = -1;
		if (command_is_redirect(token->type))
			command_ridirect_list(&(command_node->command_list->redirect_list),
									current_token);
		else
			command_word_list(&(command_node->command_list->word_list),
								current_token);
		if (!token_next(&current_token))
			return (NULL);
	}
	return (command_node);
}

t_ast	*ast_operator_node(e_ast_type type, t_ast *left_hand, t_ast *right_hand)
{
	t_ast	*ast_operator_node;

	if (right_hand == NULL)
		return (syntax_error(d)); //left_hand free
	ast_operator_node = try_calloc(1, sizeof(t_ast));
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

void	ast_addback(t_ast **head, t_ast *new_node)
{
	t_ast	*node;

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
		new_node->prev = node;
	}
	else
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		*head = new_node;
	}
}

void	command_word_list(t_command **command_list, t_token *token)
{
	t_command	*word_node;

	word_node = word_init_node(token);
	add_back_word_list(command_list, node);
}

t_word_list	*word_init_node(t_token *token)
{
	t_word_list	*node;

	node = try_calloc(1, sizeof(t_word_list));
	node->word = try_strdup(token->word);
	node->index = token->index;
	node->type = token->type;
	return (node);
}

void			word_list_addback(t_word **head, t_word *node);
{
	;
}

void	command_redirect_list(t_redirect **redirect_list,
							t_token **current_token,
							t_data *d)
{
	t_token		*token;
	t_redirect	*node;

	token = *current_token;
	node = redirect_init_node(token);
	add_back_redirect_list(redirect_list, node);
	token = token->next;
	if (token == NULL || is_operetor(token))
		syntax_error();
	node = ast_init_redirect_node(token);
	add_back_redirect_list(redirect_list, node);
	token = token->next;
	if (token == NULL || is_operetor(token))
		syntax_error();
}

//redirectのnode(<)
t_redirect_list	*redirect_init_node(t_token *token);
{
	t_redirect_list *node;
	node = try_calloc(1, sizeof(t_redirect));
	//t_redirectとtokenをstrcmpなどで比較する必要がある
	set_redirect_type(token); //redirectタイプをsetする関数
	return (node);
}

void	redirect_list_addback(t_redirect **head, t_redirect *node)
{
	;
}

//redirectのnode(word)
//これってなんだっけ？
t_redirect_list	*ast_init_redirect_word_node(t_redirect *node);
{
	t_redirect_list *node;
	node = try_calloc(1, sizeof(t_redirect));
	set_word(node->word);
	set_redirect_type(token); //redirectタイプをsetする関数
	return (node);
}

//token のindexを使う処理に変更するかも
t_token	*token_next(t_token **current_token)
{
	t_token	*token;

	token = *current_token->next;
	if (token != NULL && is_quotation_closed(token) == false)
	{
		syntax_error();
		return (NULL);
	}
	return (token);
}

void	*syntax_error(t_ast *left_node, t_ast *right_node, t_data *d)
{
	put_error("syntax_error");
	d->exit_status = hogehoge;
	d->syntax_flag = 1;
	call_heardoc();
	*ast_free_all_nodes(t_ast * left_hanf);
	*ast_free_all_nodes(t_ast * right_right);
}

void	*ast_free_all_nodes(t_ast *node)
{
	if (node != NULL && node->left_hand != NULL)
		ast_free_all_nodes(node->left_hand);
	if (node != NULL && node->right_hand != NULL)
		ast_free_all_nodes(node->right_hand);
	free(node);
	return (NULL);
}

bool	ast_is_opereter(t_token_type type)
{
	;
}

bool	command_is_redirect(t_token_type type)
{
	;
}

void	ast_expect(t_token **current_token, char op)
{
	if (current_token->kind != WORD || current_token->word[0] != op)
		error("'%c'ではありません", op);
	current_token = current_token->next;
}
