/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:28:04 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/13 19:57:56 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

bool	token_is_a_control_char(t_token_type token_type)
{
	if (token_type == TOKEN_LOGICAL_AND || \
		token_type == TOKEN_LOGICAL_OR || \
		token_type == TOKEN_PIPE || \
		token_type == REDIRECT)
		return (true);
	return (false);
}

t_token_type	token_get_last_token_type(t_token *head)
{
	t_token	*ite;

	ite = head;
	if (ite == token_end())
		return (WORD);
	else
	{
		while (ite->next != token_end())
			ite = ite->next;
	}
	return (ite->type);
}

size_t	token_can_get_next_token_index(t_token *head, char **line, \
										t_quote f_quote, size_t index)
{
	size_t			i;
	t_token_type	end_token_type;

	i = 0;
	end_token_type = token_get_last_token_type(head);
	if (f_quote == DEFAULT && \
		(ft_isspace((*line)[i]) || ft_is_special_char((*line)[i])))
	{
		index++;
		while (ft_isspace((*line)[i]))
			i++;
	}
	else if (token_is_a_control_char(end_token_type))
		index++;
	*line += i;
	return (index);
}
