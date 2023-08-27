/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:49 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/27 20:58:15 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "tokenize.h"
#include <stdlib.h>

static bool	is_quotation(char c)
{
	return (c == '\'' || c == '\"');
}

static size_t	get_size(char *word)
{
	size_t	count;

	count = 0;
	while (*word != '\0')
	{
		if (is_quotation(*word) == false)
			count++;
		word++;
	}
	return (count);
}

void	heredoc_delete_quote(t_redirect_list *delimiter)
{
	char	*old_delimiter;
	char	*new_delimiter;
	size_t	i;

	old_delimiter = delimiter->word;
	new_delimiter = try_calloc(get_size(delimiter->word) + 1, sizeof(char));
	i = 0;
	while (*old_delimiter != '\0')
	{
		if (is_quotation(*old_delimiter) == false)
		{
			new_delimiter[i] = *old_delimiter;
			i++;
		}
		old_delimiter++;
	}
	free(delimiter->word);
	delimiter->word = new_delimiter;
	// printf("%s\n", new_delimiter);
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
