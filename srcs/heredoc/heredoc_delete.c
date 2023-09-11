/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:49 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/11 16:13:45 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "tokenize.h"
#include <stdlib.h>

void	heredoc_all_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
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
