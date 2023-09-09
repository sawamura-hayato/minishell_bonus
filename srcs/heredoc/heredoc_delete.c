/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:49 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/09 20:02:03 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "tokenize.h"
#include <stdlib.h>

static bool	is_quotation(char c)
{
	return (c == '\'' || c == '\"');
}

static char	*quoted_delimiter(char *head, char **old_delimiter, char *quote,
		bool *quote_flag)
{
	char	*quoted_delimiter;
	char	*word_p;
	size_t	i;
	size_t	start;

	i = 0;
	word_p = *old_delimiter;
	start = (size_t)(word_p - head);
	while (*word_p != '\0' && *word_p != *quote)
	{
		if (*quote == '\0' && is_quotation(*word_p))
		{
			*quote = *word_p;
			*quote_flag = !(*quote_flag);
			break ;
		}
		if (*word_p == *quote)
			break ;
		word_p++;
		i++;
	}
	quoted_delimiter = try_substr(head, start, i);
	*old_delimiter = word_p;
	return (quoted_delimiter);
}

static char	*make_new_delimiter(char *head, char *old_delimiter,
		char *new_delimiter, bool quote_flag)
{
	char	quote;
	char	*tmp;

	quote = '\0';
	while (*old_delimiter != '\0')
	{
		if (is_quotation(*old_delimiter) == false || quote_flag == true)
		{
			tmp = quoted_delimiter(head, &old_delimiter, &quote, &quote_flag);
			if (new_delimiter == NULL)
				new_delimiter = try_strdup(tmp);
			else
				new_delimiter = try_strjoin_free(new_delimiter, tmp);
			free(tmp);
		}
		else
		{
			quote_flag = !quote_flag;
			quote = *old_delimiter;
		}
		if (*old_delimiter == '\0')
			break ;
		old_delimiter++;
	}
	return (new_delimiter);
}

void	heredoc_delete_quote(t_redirect_list *delimiter)
{
	char	*old_delimiter;
	char	*new_delimiter;
	bool	quote_flag;

	old_delimiter = delimiter->word;
	new_delimiter = NULL;
	quote_flag = false;
	new_delimiter = make_new_delimiter(delimiter->word, &(*old_delimiter),
			&(*new_delimiter), quote_flag);
	free(delimiter->word);
	delimiter->word = new_delimiter;
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
