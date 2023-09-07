/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:36:12 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/05 15:53:46 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	word_list_free(t_word_list *word_list)
{
	free(word_list->word);
	free(word_list->type);
	free(word_list);
}

void	word_list_delete_head(t_word_list **head)
{
	t_word_list	*node;
	t_word_list	*tmp;

	node = *head;
	if (node == NULL)
		return ;
	tmp = node->next;
	word_list_free(node);
	*head = tmp;
}

void	word_list_delete_tail(t_word_list **head)
{
	t_word_list	*node;

	node = *head;
	if (node == NULL || node->next == NULL)
		return ;
	while (node->next->next != NULL)
		node = node->next;
	word_list_free(node->next);
	node->next = NULL;
}

void	word_list_delete_target(t_word_list **head, t_word_list *target)
{
	t_word_list	*tmp;
	t_word_list	*node;

	if (*head == target)
	{
		*head = target->next;
		word_list_free(target);
		return ;
	}
	node = *head;
	while (node->next != NULL && node->next != target)
		node = node->next;
	if (node->next != NULL)
	{
		tmp = node->next->next;
		word_list_free(node->next);
		node->next = tmp;
	}
}
