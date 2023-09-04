/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_delete_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:39:09 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/03 13:54:27 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_is_type_quotation(char type)
{
	if (type == IS_SINGLE_QUOTED || type == IS_DOUBLE_QUOTED)
		return (true);
	return (false);
}

size_t	expand_get_size_delete_quotation_word(char *word)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (word[i] != '\0')
	{
		if (!expand_is_type_quotation(word[i]))
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
		if (expand_is_type_quotation(word[i]))
			return (true);
		i++;
	}
	return (false);
}

// void	expand_delete_quotation_word_list(t_word_list *word_list)
// {
// 	expand_delete_quotation_word_list(word_list);
// }

// void	expand_delete_quotation_redirect_list(t_redirect_list *redirect_list)
// {
// 	expand_delete_quotation_word_list(redirect_list);
// }
