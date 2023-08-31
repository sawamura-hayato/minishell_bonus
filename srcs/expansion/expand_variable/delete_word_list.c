/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:36:12 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 12:02:22 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	word_list_free(t_word_list *word_list)
{
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

	node = *head;
	while (node->next != NULL && ft_strcmp(node->next->word, target->word))
		node = node->next;
	if (node->next != NULL)
	{
		tmp = node->next->next;
		word_list_free(node->next);
		node->next = tmp;
	}
}
