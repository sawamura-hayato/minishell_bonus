/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_linked_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:57:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/05 18:39:04 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdlib.h>
#include <stdio.h>

t_token	*token_end(void)
{
	return (NULL);
}

void	token_addback(t_token **head, t_token *new_token)
{
	t_token	*ite;

	ite = *head;
	if (ite == token_end())
		*head = new_token;
	else
	{
		while (ite->next != token_end())
			ite = ite->next;
		ite->next = new_token;
	}
}

t_token	*create_token(char *word, t_token_type token_type, size_t index)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->word = word;
	token->type = token_type;
	token->index = index;
	token->next = NULL;
	return (token);
}

void	debug_print_token(t_token *token_list)
{
	while (token_list != NULL)
	{
		printf("word            [%s]\n", token_list->word);
		printf("token token_type  [%d]\n", token_list->type);
		printf("token n         [%zu]\n", token_list->index);
		token_list = token_list->next;
	}
}

void	free_token(t_token *token_list)
{
	t_token	*tmp_token;

	tmp_token = NULL;
	while (token_list != NULL)
	{
		free(token_list);
		tmp_token = token_list->next;
		token_list = tmp_token;
	}
}

// void	free_token(t_token *token_list);
// int main()
// {
// 	t_token	*head;
// 	t_token	*token;
// 	head = NULL;
// 	token = create_token("get", WORD, 1);
// 	token_addback(&head, token);
// 	token = create_token("good", WORD, 2);
// 	token_addback(&head, token);
// 	debug_print_token(head);
// 	free_token(head);
// 	return (0);
// }

// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }