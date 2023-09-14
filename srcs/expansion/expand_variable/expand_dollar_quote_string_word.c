/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_quote_string_word.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:51:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/14 13:31:22 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_is_delete_dollar_quote(char *word, char *type)
{
	size_t	i;

	i = 0;
	if (type == NULL)
		return (false);
	while (word[i] != '\0')
	{
		if (IS_DOUBLE_QUOTED == type[i])
		{
			while (IS_DOUBLE_QUOTED != type[++i])
			{
				if (type[i] == '\0')
					return (false);
			}
		}
		if (word[i] == '$' && \
			(IS_SINGLE_QUOTED == type[i + 1] || \
			IS_DOUBLE_QUOTED == type[i + 1]))
			return (true);
		i++;
	}
	return (false);
}

static size_t	get_size_delete_dollar_quote(char *word, char *type)
{
	
	size_t	i;

	i = 0;
	if (type == NULL)
		return (false);
	while (type[i] != '\0')
	{
		if (IS_DOUBLE_QUOTED == type[i])
		{
			i++;
			while (IS_DOUBLE_QUOTED != type[i])
				i++;
		}
		if (word[i] == '$' && DEFAULT_CHAR_TYPE != type[i + 1])
			return (i);
		i++;
	}
	return (i);
}

static char	*get_delete_dollar_quote_word(char *word, size_t index_dollar)
{
	char	*new_word;
	char	*s_dollar_word;
	char	*e_dollar_word;

	s_dollar_word = try_substr((const char *)word, 0, index_dollar);
	e_dollar_word = try_strdup((&word[index_dollar + 1]));
	new_word = try_strjoin(s_dollar_word, e_dollar_word);
	free(s_dollar_word);
	free(e_dollar_word);
	return(new_word);
}

static char	*get_delete_dollar_quote_type(char *type, size_t index_dollar)
{
	char	*new_type;
	char	*s_dollar_type;
	char	*e_dollar_type;

	s_dollar_type = try_substr((const char *)type, 0, index_dollar);
	e_dollar_type = try_strdup((&type[index_dollar + 1]));
	new_type = try_strjoin(s_dollar_type, e_dollar_type);
	free(s_dollar_type);
	free(e_dollar_type);
	return(new_type);
}

void	expand_get_delete_dollar_quote(char **word, char **type)
{
	char	*new_word;
	char	*new_type;
	size_t	index_dollar;

	index_dollar = get_size_delete_dollar_quote(*word, *type);
	new_word = get_delete_dollar_quote_word(*word, index_dollar);
	new_type = get_delete_dollar_quote_type(*type, index_dollar);
	free(*word);
	*word = new_word;
	free(*type);
	*type = new_type;
}
