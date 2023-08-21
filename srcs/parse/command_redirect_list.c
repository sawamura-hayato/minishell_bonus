#include "parse.h"
#include "ft.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

static t_redirect_list *get_last_redirect_List_node(t_redirect_list **head)
{
	t_redirect_list *p;
	
	p = *head;
	while(p)
	{
		if(p->next == NULL)
			break;
		p = p -> next;
	}
	return(p);
}

static void	redirect_set_type2(t_redirect_list *last_node, t_redirect_list*node,t_token *token)
{
	printf("last_node:%s\n",last_node->word);
	printf("token:%s\n",token->word);
	if(last_node->type == PS_REDIRECTING_INPUT 
			|| last_node->type == PS_FILE)	
	{
		if(ft_strcmp(token->word,"'") == 0) 
			node->type = PS_REDIRECT_SINGLE_QUOTE; 
		else if(ft_strcmp(token->word,"\"") == 0) 
			node->type = PS_REDIRECT_DOUBLE_QUOTE; 
		else
			node->type = PS_FILE;
	}
	else if(last_node->type == PS_HERE_DOCUMENTS)
	{
		if(ft_strchr(token->word,'\'') == NULL) 
			node->type = PS_DELIMITER ;
		else
			node-> type = PS_QUOTE_DELIMITER ;
	}
	else
		node->type = PS_FILE;
}

static void	redirect_set_type(t_redirect_list **head,t_redirect_list *node,t_token *token)
{
	t_redirect_list *last_node;

	last_node = get_last_redirect_List_node(head);
	if(last_node != NULL)
		redirect_set_type2(last_node,node,token);
	else
	{
		if(ft_strcmp(token->word,"<") == 0)
			node->type = PS_REDIRECTING_INPUT;
		else if(ft_strcmp(token->word,">") == 0)
			node->type = PS_REDIRECTING_OUTPUT;
		else if(ft_strcmp(token->word,">>") == 0)
			node->type = PS_APPENDING_OUTPUT;
		else if(ft_strcmp(token->word,"<<") == 0)
			node->type = PS_HERE_DOCUMENTS;
	}
}

static t_redirect_list	*redirect_init_node(t_redirect_list **head,t_token *token,bool redirect_flag)
{
	t_redirect_list *node;
	node = try_calloc(1, sizeof(t_redirect_list));
	if(redirect_flag == true)
		node->word = try_strdup(token->word);
	//t_redirectとtokenをstrcmpなどで比較する必要がある
	redirect_set_type(head,node,token); //redirectタイプをsetする関数
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
	node = redirect_init_node(head,token,redirect_flag);
	if(redirect_flag==false && token->next == NULL)
	{
		d->syntax_flag = true;
		ast_syntax_error(d);
	}
	redirect_list_addback(head, node);
}
