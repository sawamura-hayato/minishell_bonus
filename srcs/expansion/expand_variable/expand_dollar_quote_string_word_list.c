/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_quote_string_word_list.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:51:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/15 14:52:03 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void expand_delete_dollar_quote_word_list(t_word_list **head, bool is_head_dollar)
{
	t_word_list *node;

	node = *head;
	if (is_head_dollar)
	{
		word_list_delete_head(head);
		word_list_delete_head(head);
		word_list_delete_taget(head, (*head)->next);
	}
	else
	{
		while (ft_strcmp((*head)->next->word, "$"))
			(*head) = (*head)->next;
		word_list_delete_taget(head, (*head)->next);
		word_list_delete_taget(head, (*head)->next);
		if ((*head)->next->next == NULL)
			word_list_delete_tail(head);
		else
			word_list_delete_taget(head, (*head)->next->next);
		(*head) = node;
	}
}

void expand_dollar_quote_string_word_list(t_word_list **head)
{
	t_word_list *node;

	if (!ft_strcmp((*head)->word, "$") &&
		((*head)->next->type == SINGLE_QUOTE || (*head)->next->type == DOUBLE_QUOTE))
		expand_delete_dollar_quote_word_list(head, true);
	node = *head;
	while ((*head) != NULL && (*head)->next != NULL && (*head)->next->next != NULL)
	{
		if (!ft_strcmp((*head)->next->word, "$") &&
			((*head)->next->next->type == SINGLE_QUOTE ||
			 (*head)->next->next->type == DOUBLE_QUOTE))
			expand_delete_dollar_quote_word_list(head, false);
		*head = (*head)->next;
	}
	*head = node;
}

bool expand_is_dollar_quote_string_word_list(t_word_list *head)
{
	t_word_list *node;

	node = head;
	if (node == NULL || node->next == NULL)
		return (false);
	if (!ft_strcmp(node->word, "$") &&
		(node->next->type == SINGLE_QUOTE || node->next->type == DOUBLE_QUOTE))
		return (true);
	while (node->next->next != NULL)
	{
		if (!ft_strcmp(node->next->word, "$") &&
			(node->next->next->type == SINGLE_QUOTE || node->next->next->type == DOUBLE_QUOTE))
			return (true);
		node = node->next;
	}
	return (false);
}

t_word_list *expand_can_dollar_quote_string_word_list(t_word_list **head)
{
	if (expand_is_dollar_quote_string_word_list(*head))
		expand_dollar_quote_string_word_list(head);
	return (*head);
}
