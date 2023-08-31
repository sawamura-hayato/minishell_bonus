/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_delete_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:39:09 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 17:59:13 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_is_type_quotation(int type)
{
	if (type == IS_SINGLE_QUOTED || type == IS_DOUBLE_QUOTED)
		return (true);
	return (false);
}

static size_t	expand_get_size_delete_quotation_word(char *word)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (word[i] != '\0')
	{
		if (!expand_is_type_quotation(word[i] - '0'))
			size++;
		i++;
	}
	return (size);
}

bool	expand_is_delete_quotation_word(char *word)
{
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0')
	{
		if (expand_is_type_quotation(word[i] - '0'))
			return (true);
		i++;
	}
	return (false);
}

void	expand_delete_quotation_word_list(t_word_list *word_list)
{
	char	*new_word;
	char	*new_type;
	size_t	i;
	size_t	new_index;
	size_t	size;

	size = expand_get_size_delete_quotation_word(word_list->type);
	new_word = try_calloc(size + 1, sizeof(char));
	new_type = try_calloc(size + 1, sizeof(char));
	i = 0;
	new_index = 0;
	while (word_list->type[i] != '\0')
	{
		if (!expand_is_type_quotation(word_list->type[i] - '0'))
		{
			new_word[new_index] = word_list->word[i];
			new_type[new_index] = word_list->type[i];
			new_index++;
		}
		i++;
	}
	word_list->word = new_word;
	word_list->type = new_type;
}

void	expand_delete_quotation_redirect_list(t_redirect_list *redirect_list)
{
	char	*new_word;
	char	*new_type;
	size_t	i;
	size_t	new_index;
	size_t	size;

	size = expand_get_size_delete_quotation_word(redirect_list->type);
	new_word = try_calloc(size + 1, sizeof(char));
	new_type = try_calloc(size + 1, sizeof(char));
	i = 0;
	new_index = 0;
	while (redirect_list->type[i] != '\0')
	{
		if (!expand_is_type_quotation(redirect_list->type[i] - '0'))
		{
			new_word[new_index] = redirect_list->word[i];
			new_type[new_index] = redirect_list->type[i];
			new_index++;
		}
		i++;
	}
	free(redirect_list->word);
	free(redirect_list->type);
	redirect_list->word = new_word;
	redirect_list->type = new_type;
}

// void	expand_delete_quotation_word_list(t_word_list *word_list)
// {
// 	expand_delete_quotation_word_list(word_list);
// }

// void	expand_delete_quotation_redirect_list(t_redirect_list *redirect_list)
// {
// 	expand_delete_quotation_word_list(redirect_list);
// }
