/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_str_to_dollar.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:37:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/03 19:20:21 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "library.h"
#include "tokenize.h"

bool	export_is_symbol(char c);

static size_t	expand_get_string_to_dollar_or_symbol_size(char *word)
{
	size_t	size;

	size = 0;
	while (word[size] != '\0' && \
			(!export_is_symbol(word[size])) && \
			(!ft_isspace(word[size])))
		size++;
	return (size);
}

char	*expand_get_string_to_dollar_or_symbol(char **word)
{
	char	*str;
	size_t	size;
	size_t	i;

	size = expand_get_string_to_dollar_or_symbol_size(*word);
	i = 0;
	str = try_calloc(size + 1, sizeof(char));
	while (i < size)
	{
		str[i] = (*word)[i];
		i++;
	}
	(*word) += size;
	return (str);
}

static size_t	expand_get_str_to_dollar_size(char *word, char *type)
{
	size_t	i;

	i = 0;
	while (type[i] != '\0' && word[i] != '$')
	{
		if (IS_SINGLE_QUOTED == type[i])
		{
			while (IS_SINGLE_QUOTED != type[++i])
			{
				if (type[i] == '\0')
					return (i);
			}
		}
		i++;
	}
	return (i);
}

char	*expand_get_str_to_dollar(char **word, char *type)
{
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	if (type == NULL)
		return (NULL);
	size = expand_get_str_to_dollar_size(*word, type);
	str = try_calloc(size + 1, sizeof(char));
	while (i < size)
	{
		str[i] = (*word)[i];
		i++;
	}
	*word += size;
	return (str);
}
