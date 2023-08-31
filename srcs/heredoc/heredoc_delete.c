/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                    +:+ +:+         +:+     */
/*   heredoc_delete.c                                   :+:      :+:    :+:   */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:49 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/30 19:15:39 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "tokenize.h"
#include <stdlib.h>

static bool	is_quotation(char c)
{
	return (c == '\'' || c == '\"');
}

/* static size_t	get_size(char *word) */
/* { */
/* 	size_t	count; */

/* 	count = 0; */
/* 	while (*word != '\0') */
/* 	{ */
/* 		if (is_quotation(*word) == false) */
/* 			count++; */
/* 		word++; */
/* 	} */
/* 	return (count); */
/* } */
static char * quoted_delimiter(char *head,char **old_delimiter,char quote)
{
		char *quoted_delimiter;
		char *word_p;
		size_t i;
		size_t start;

		i = 0;
		word_p = *old_delimiter;
		start = (size_t)(word_p - head);
		while(*word_p != '\0' || *word_p != quote)
 		{
				if(quote == '\0' && is_quotation(*word_p))
								break;
				word_p++;
				i++;
		}
		quoted_delimiter = try_substr(head,start,i);
		return(quoted_delimiter);
}

void	heredoc_delete_quote(t_redirect_list *delimiter)
{
	char	*old_delimiter;
	char	*new_delimiter;
	bool 	quote_flag;
	char 	quote;
	char 	*tmp;

	old_delimiter = delimiter->word;
	new_delimiter = NULL;
	quote_flag = false;
	quote = '\0';
	while (*old_delimiter != '\0')
	{
		if (is_quotation(*old_delimiter) == false || quote_flag == true)
			tmp = quoted_delimiter(delimiter->word,&old_delimiter,quote);
		else
		{
			quote_flag = !quote_flag ;
			quote = *old_delimiter;
		}
		old_delimiter++;
	}
	if(new_delimiter == NULL)
	{
		new_delimiter = try_strdup(tmp);
		free(tmp);
	}
	else
		try_strjoin_free(new_delimiter,tmp);
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
