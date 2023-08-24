/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:49 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/23 19:48:52 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

void	heredoc_delete_quote(t_redirect_list *delimiter)
{
	(void)delimiter;
}

void	redirect_delete(t_command *command, t_redirect_list *target)
{
	t_redirect_list	*list_p;
	t_redirect_list	*prev;

	list_p = command->redirect_list;
	if (list_p == target)
	{
		command->redirect_list = list_p->next;
		free(list_p);
		return ;
	}
	prev = list_p;
	while (list_p)
	{
		if (list_p == target)
		{
			prev->next = list_p->next;
			free(list_p);
			break ;
		}
		prev = list_p;
		list_p = list_p->next;
	}
}
