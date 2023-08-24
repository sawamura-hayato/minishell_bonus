/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:54:13 by hsawamur          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/22 13:13:51 by hsawamur         ###   ########.fr       */
=======
/*   Updated: 2023/08/15 16:39:12 by hsawamur         ###   ########.fr       */
>>>>>>> 106-単語分割
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void redirect_free(t_redirect_list *redirect)
{
	// free(redirect->word);
	free(redirect);
}

void redirect_delete_head(t_redirect_list **head)
{
	t_redirect_list *node;
	t_redirect_list *tmp;

	node = *head;
	if (node == NULL)
		return;
	tmp = node->next;
	redirect_free(node);
	*head = tmp;
}

void redirect_delete_tail(t_redirect_list **head)
{
	t_redirect_list *node;

	node = *head;
	if (node == NULL || node->next == NULL)
		return;
	while (node->next->next != NULL)
		node = node->next;
	redirect_free(node->next);
	node->next = NULL;
}

<<<<<<< HEAD
void redirect_delete_target(t_redirect_list **head, t_redirect_list *target)
=======
void redirect_delete_taget(t_redirect_list **head, t_redirect_list *target)
>>>>>>> 106-単語分割
{
	t_redirect_list *tmp;
	t_redirect_list *node;

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
