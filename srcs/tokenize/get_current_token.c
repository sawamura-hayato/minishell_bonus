/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:18:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/06 13:41:09 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "tokenize.h"
#include "library.h"

size_t token_get_special_word_size(char *line)
{
	size_t size;
	size_t logical_or_size;
	size_t logical_and_size;
	size_t pipe_size;

	size = 0;
	logical_or_size = 2;
	logical_and_size = 2;
	pipe_size = 1;
	if ('|' == line[0])
	{
		if ('|' == line[1])
			return (logical_or_size);
		return (pipe_size);
	}
	else if ('&' == line[0])
	{
		if ('&' == line[1])
			return (logical_and_size);
		return (++size);
	}
	return (size);
}

size_t token_get_current_word_size(char *line, t_quote f_quote)
{
	size_t size;

	size = token_get_special_word_size(line);
	if (f_quote != DEFAULT)
	{
		while (f_quote != token_set_flag_quote(line[size]) && line[size] != '\0')
			size++;
	}
	else
	{
		while (token_set_flag_quote(line[size]) == DEFAULT &&
			   !ft_isspace(line[size]) &&
			   !ft_is_special_char(line[size]) &&
			   line[size] != '\0')
			size++;
	}
	return (size);
}

char *token_get_current_word(char *line, size_t size)
{
	size_t i;
	char *word;

	word = try_calloc(0, sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		word[i] = line[i];
		i++;
	}
	return (word);
}

void token_get_current_token(t_token **head,
							 char **line,
							 t_quote f_quote,
							 size_t *index)
{
	t_token *current_token;
	size_t size;
	char *word;
	t_token_type current_token_type;

	size = token_get_current_word_size(*line, f_quote);
	word = token_get_current_word(*line, size);
	current_token_type = token_set_flag_token(word, f_quote);
	current_token = create_token(word, current_token_type, *index);
	token_addback(head, current_token);
	*line += size;
}
