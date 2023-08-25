/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_word_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:58:47 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/25 16:51:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

size_t	token_get_operator_size(char *line)
{
	size_t	size;
	size_t	logical_or_size;
	size_t	logical_and_size;
	size_t	pipe_size;

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
	else if ('(' == line[0] || ')' == line[0])
		return (++size);
	return (size);
}

size_t	token_get_redirect_list_size(char *line)
{
	size_t	size;
	size_t	redirect_input;
	size_t	redirect_output;

	size = 0;
	redirect_input = 1;
	redirect_output = 1;
	if ('<' == line[0])
	{
		if ('<' == line[1])
			return (++redirect_input);
		return (redirect_input);
	}
	else if ('>' == line[0])
	{
		if ('>' == line[1])
			return (++redirect_output);
		return (redirect_output);
	}
	return (size);
}

size_t	token_get_special_word_size(char *line)
{
	size_t	size;

	size = 0;
	size += token_get_operator_size(line);
	size += token_get_redirect_list_size(line);
	return (size);
}

size_t	token_get_current_word_size(char *line)
{
	size_t	size;
	t_quote	f_quote;

	size = 0;
	while (line[size] != '\0')
	{
		f_quote = token_set_flag_quote(line[size]);
		if (f_quote != DEFAULT)
		{
			size++;
			while (f_quote != token_set_flag_quote(line[size]))
			{
				if (line[size] == '\0')
				{
					size--;
					break;
				}
				size++;
			}
		}
		else if (ft_isspace(line[size]) || \
					ft_is_special_char(line[size]))
			break;
		size++;
	}
	size += token_get_special_word_size(line);
	return (size);
}
