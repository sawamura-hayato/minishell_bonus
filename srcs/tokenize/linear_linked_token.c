/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_linked_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:57:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/04 18:26:37 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_token	*token_end(void)
{
	return (NULL);
}
t_token_type	token_last_token_type(t_token *head)
{
	t_token	*ite;

	ite = head;
	if (ite == token_end())
		return (WORD);
	else
	{
		while (ite->next != token_end())
			ite = ite->next;
	}
	return (ite->type);
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