/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:54:13 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/16 09:54:41 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void redirect_free(t_redirect *redirect)
{
	// free(redirect->word);
	free(redirect);
}

void redirect_delete_head(t_redirect **head)
{
	t_redirect *node;
	t_redirect *tmp;

	node = *head;
	if (node == NULL)
		return;
	tmp = node->next;
	redirect_free(node);
	*head = tmp;
}

void redirect_delete_tail(t_redirect **head)
{
	t_redirect *node;

	node = *head;
	if (node == NULL || node->next == NULL)
		return;
	while (node->next->next != NULL)
		node = node->next;
	redirect_free(node->next);
	node->next = NULL;
}

void redirect_delete_target(t_redirect **head, t_redirect *target)
{
	t_redirect *tmp;
	t_redirect *node;

	node = *head;
	while (node->next != NULL && ft_strcmp(node->next->word, target->word))
		node = node->next;
	if (node->next != NULL)
	{
		tmp = node->next->next;
		redirect_free(node->next);
		node->next = tmp;
	}
}
