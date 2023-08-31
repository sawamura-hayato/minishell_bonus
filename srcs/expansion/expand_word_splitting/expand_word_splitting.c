/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:30:36 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 17:16:02 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_is_quoted(char *type, size_t size)
{
	size_t	i;
	bool	f_quote;

	i = 0;
	f_quote = false;
	while (i < size)
	{
		if (IS_DOUBLE_QUOTED == type[i] - '0')
			f_quote = !f_quote;
		i++;
	}
	return (f_quote);
}

bool	expand_have_ifs(char *word, char *ifs)
{
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0' && !expand_is_str_in_char(ifs, word[i]))
		i++;
	if (word[i] == '\0')
		return (false);
	return (true);
}
