/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_word_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:23:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/18 12:21:47 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int		printf(const char *format, ...);

void word_list_new_head(t_word_list **head, t_word_list *new_word_list)
{
	if (new_word_list != NULL)
	{
		new_word_list->next = *head;
		*head = new_word_list;
	}
}

void word_list_new_tail(t_word_list **head, t_word_list *new_word_list)
{
	t_word_list *node;

	node = *head;
	while (node->next != NULL)
		node = node->next;
	node->next = new_word_list;
}

void word_list_new_target(t_word_list **head, t_word_list *target, t_word_list *new_word_list)
{
	t_word_list *node;
	t_word_list *tmp;

	node = *head;
	// printf("head     %s\n", node->word);
	while (node->next != NULL && ft_strcmp(node->word, target->word))
		node = node->next;
	// printf("head     %s\n", node->word);
	// printf("target   %s\n", target->word);
	// printf("new      %s\n", new_word_list->word);
	tmp = node->next;
	node->next = new_word_list;
	new_word_list->next = tmp;
}
