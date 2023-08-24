/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:34:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/14 19:01:33 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdbool.h>

char *get_quote_token(t_quote f_quote)
{
	if (SINGLE_QUOTE_FLAG == f_quote)
		return ("\'");
	else if (DOUBLE_QUOTE_FLAG == f_quote)
		return ("\"");
	return (NULL);
}

bool token_can_get_quote_token(t_token **head, char **line,
							   t_quote *f_quote, size_t index)
{
	t_quote first_char;
	t_token *quote_token;

	first_char = token_set_flag_quote(*line[0]);
	if (*f_quote != DEFAULT && *f_quote == first_char)
	{
		*f_quote = DEFAULT;
		quote_token = create_token(get_quote_token(first_char),
								   token_set_flag_token(*line, DEFAULT), index);
		token_addback(head, quote_token);
		(*line)++;
		return (true);
	}
	else if (*f_quote == DEFAULT && first_char != DEFAULT)
	{
		*f_quote = first_char;
		quote_token = create_token(get_quote_token(first_char),
								   token_set_flag_token(*line, DEFAULT), index);
		token_addback(head, quote_token);
		(*line)++;
		return (true);
	}
	else if (**line == '\0')
		return (true);
	return (false);
}
