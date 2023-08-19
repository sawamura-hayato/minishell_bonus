#include "parse.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

static void	redirect_set_type(t_redirect_list *node,t_token *token)
{
	if(ft_strcmp(token->word,"<") == 0)
		node->type = PS_REDIRECTING_INPUT;
	else if(ft_strcmp(token->word,">") == 0)
		node->type = PS_REDIRECTING_OUTPUT;
	else if(ft_strcmp(token->word,">>") == 0)
		node->type = PS_APPENDING_OUTPUT;
	else if(ft_strcmp(token->word,"<<") == 0)
		node->type = PS_HERE_DOCUMENTS;
	else if(ft_strcmp(token->word,"<<") == 0)
		node->type = PS_HERE_DOCUMENTS;
}

static t_redirect_list	*redirect_init_node(t_token *token,bool redirect_flag)
{
	t_redirect_list *node;
	node = try_calloc(1, sizeof(t_redirect_list));
	if(redirect_flag == true)
		node->word = try_strdup(token->word);
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
							t_data *d,bool redirect_flag)
{
	t_token		*token;
	t_redirect_list	*node;

	token = *current_token;
	node = redirect_init_node(token,redirect_flag);
	if(redirect_flag==false && token->next == NULL)
	{
		d->syntax_flag = true;
		ast_syntax_error(d);
	}
	printf("command_redirect:%s\n",token->word);
	redirect_list_addback(head, node);
}
