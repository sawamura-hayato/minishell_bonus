/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list_delete_quote.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:00:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/06 20:00:28 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	expand_delete_quotation_word_list_until(t_word_list *word_list, \
													char **new_word, \
													char **new_type)
{
	size_t	i;
	size_t	new_index;
	bool	is_in_quote;

	i = 0;
	new_index = 0;
	is_in_quote = false;
	while (word_list->type[i] != '\0')
	{
		if (!expand_is_type_quotation(word_list->type[i]))
		{
			(*new_word)[new_index] = word_list->word[i];
			if (is_in_quote)
				(*new_type)[new_index] = IS_IN_QUOTED;
			else
				(*new_type)[new_index] = word_list->type[i];
			new_index++;
		}
		else
			is_in_quote = !is_in_quote;
		i++;
	}
}

void	expand_delete_quotation_word_list(t_word_list *word_list)
{
	char	*new_word;
	char	*new_type;
	size_t	size;

	size = expand_get_size_delete_quotation_word(word_list->type);
	new_word = try_calloc(size + 1, sizeof(char));
	new_type = try_calloc(size + 1, sizeof(char));
	expand_delete_quotation_word_list_until(word_list, &new_word, &new_type);
	free(word_list->word);
	free(word_list->type);
	word_list->word = new_word;
	word_list->type = new_type;
}
