/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_word_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:23:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/30 10:47:12 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int		printf(const char *format, ...);

void	word_list_new_head(t_word_list **head, t_word_list *new_word_list)
{
	if (new_word_list != NULL)
	{
		new_word_list->next = *head;
		*head = new_word_list;
	}
}

void	word_list_new_tail(t_word_list **head, t_word_list *new_word_list)
{
	t_word_list	*node;

	node = *head;
	if (node == NULL)
	{
		*head = new_word_list;
		return ;
	}
	while (node->next != NULL)
		node = node->next;
	node->next = new_word_list;
}

void	word_list_new_target(t_word_list **head, t_word_list *target, \
								t_word_list *new_word_list)
{
	t_word_list	*node;
	t_word_list	*tmp;

	node = *head;
	if (node == NULL)
		return (word_list_new_tail(head, new_word_list));
	while (node->next != NULL && ft_strcmp(node->word, target->word))
		node = node->next;
	tmp = node->next;
	node->next = new_word_list;
	new_word_list->next = tmp;
}
