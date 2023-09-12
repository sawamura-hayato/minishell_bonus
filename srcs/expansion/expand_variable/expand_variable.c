/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:21:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/12 16:22:12 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_is_str_in_char(char *str, char c)
{
	if (str == NULL)
		return (false);
	while (*str != '\0')
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

bool	expand_is_variable_word(char *word, char *type)
{
	char	f_quote;
	size_t	i;

	i = 0;
	if (type == NULL)
		return (false);
	while (type[i] != '\0')
	{
		f_quote = type[i];
		if (IS_SINGLE_QUOTED == f_quote)
		{
			while (IS_SINGLE_QUOTED != (type[++i]))
			{
				if (type[i] == '\0')
					return (false);
			}
		}
		else
		{
			if (word[i] == '$')
				return (true);
		}
		i++;
	}
	return (false);
}

void	expand_variable_word_list(t_word_list *word_list, t_data *d)
{
	if (expand_is_variable_word(word_list->word, word_list->type))
	{
		expand_get_expanded_token(&(word_list->word), &(word_list->type), d);
	}
}

void	expand_variable_redirect_list(t_redirect_list *redirect_list, \
										t_data *d, char *ifs)
{
	char	*word;
	char	*type;

	word = try_strdup(redirect_list->word);
	type = try_strdup(redirect_list->type);
	if (expand_is_variable_word(redirect_list->word, redirect_list->type))
	{
		expand_get_expanded_token(&(redirect_list->word), \
									&(redirect_list->type), d);
		if (expand_is_ambiguous_error(redirect_list->word, \
									redirect_list->type, ifs))
		{
			redirect_list->is_ambiguous_error = true;
			free(redirect_list->word);
			free(redirect_list->type);
			redirect_list->word = word;
			redirect_list->type = type;
		}
		else
		{
			free(word);
			free(type);
		}
	}
}
