#include "parse.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

static t_word_list	*word_list_init_node(t_token *token)
{
	t_word_list	*node;

	printf("token is:%s\n",token->word);
	node = try_calloc(1, sizeof(t_word_list));
	node->word = try_strdup(token->word);
	node->index = token->index;
	node->type = token->type;
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

void	command_word_list(t_word_list **head, t_token **current_token)
{
	t_word_list	*word_node;
	t_token *token;

	token = *current_token;
	while(token!=NULL && token->next == 0)
	{
		word_node = word_list_init_node(token);
		printf("word_node->word is:%s\n",word_node->word);
		word_list_addback(head, word_node);
		token = token->next;
	}
	(*current_token) = token;
}

