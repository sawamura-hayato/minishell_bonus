#include "parse.h"

static t_word_list	*word_list_init_node(t_token *token)
{
	t_word_list	*node;

	node = try_calloc(1, sizeof(t_word_list));
	node->word = try_strdup(token->word);
	node->type = try_strdup(token->type);
	node->type = token->tk_type;
	return (node);
}

static void			word_list_addback(t_word_list **head, t_word_list *new_node)
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

void	command_word_list(t_word_list **head, t_token **current_token,t_data *d)
{
	t_word_list	*word_node;
	t_token *token;

	token = *current_token;
	if(token_is_quotation_closed(token)==false)
	{
		d->syntax_flag = true;
		ast_syntax_error(d,token);
	}
	else
	{
		word_node = word_list_init_node(token);
		word_list_addback(head, word_node);
	}
}

