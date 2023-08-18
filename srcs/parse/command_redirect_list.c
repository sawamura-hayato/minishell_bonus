#include "parse.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

static void	redirect_set_type(t_redirect_list *node,t_token *token)
{
	if(token->word[0] == '<')
		node->type = PS_REDIRECTING_INPUT;
}

static t_redirect_list	*redirect_init_node(t_token *token)
{
	t_redirect_list *node;
	node = try_calloc(1, sizeof(t_redirect_list));
	//t_redirectとtokenをstrcmpなどで比較する必要がある
	redirect_set_type(node,token); //redirectタイプをsetする関数
	return (node);
}

static void	redirect_list_addback(t_redirect_list **head, t_redirect_list *new_node)
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
