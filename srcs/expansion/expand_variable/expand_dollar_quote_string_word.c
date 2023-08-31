/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_quote_string_word.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:51:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 12:04:00 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*expand_get_delete_dollar_quote(char **word, t_quote f_quote)
{
	char	*expand_word;
	size_t	size;
	size_t	i;

	size = 0;
	(*word)++;
	while (f_quote != token_set_flag_quote((*word)[size]))
		size++;
	expand_word = try_calloc(size + 1, sizeof(char));
	i = 0;
	while (i < size)
	{
		expand_word[i] = (*word)[i];
		i++;
	}
	(*word) += size + 1;
	return (expand_word);
}
