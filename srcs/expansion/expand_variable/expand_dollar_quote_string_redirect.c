/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_quote_string_redirect.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:49:50 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/15 14:51:04 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void expand_token_redirect(t_redirect *redirect, t_data *d)
{
	char *expand_word;

	expand_word = expand_get_expanded_token(redirect->word, d);
	redirect->word = expand_word;
}

void expand_delete_dollar_quote_redirect(t_redirect **head, bool is_head_dollar)
{
	t_redirect *node;

	node = *head;
	if (is_head_dollar)
	{
		redirect_delete_head(head);
		redirect_delete_head(head);
		redirect_delete_taget(head, (*head)->next);
	}
	else
	{
		while (ft_strcmp((*head)->next->word, "$"))
			(*head) = (*head)->next;
		redirect_delete_taget(head, (*head)->next);
		redirect_delete_taget(head, (*head)->next);
		if ((*head)->next->next == NULL)
			redirect_delete_tail(head);
		else
			redirect_delete_taget(head, (*head)->next->next);
		(*head) = node;
	}
}

void expand_dollar_quote_string_redirect(t_redirect **head)
{
	t_redirect *node;

	if (!ft_strcmp((*head)->word, "$") &&
		((*head)->next->type == SINGLE_QUOTE || (*head)->next->type == DOUBLE_QUOTE))
		expand_delete_dollar_quote_redirect(head, true);
	node = *head;
	while ((*head) != NULL && (*head)->next != NULL && (*head)->next->next != NULL)
	{
		if (!ft_strcmp((*head)->next->word, "$") &&
			((*head)->next->next->type == SINGLE_QUOTE ||
			 (*head)->next->next->type == DOUBLE_QUOTE))
			expand_delete_dollar_quote_redirect(head, false);
		*head = (*head)->next;
	}
	*head = node;
}

bool expand_is_dollar_quote_string_redirect(t_redirect *head)
{
	t_redirect *node;

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

t_redirect *expand_can_dollar_quote_string_redirect(t_redirect **head)
{
	if (expand_is_dollar_quote_string_redirect(*head))
		expand_dollar_quote_string_redirect(head);
	return (*head);
}
