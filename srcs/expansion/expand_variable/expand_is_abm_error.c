/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_is_abm_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:01:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/09 19:03:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool	expand_is_amb_error_unil(char *word, char *type, \
										size_t i, char *ifs)
{
	bool	flag;

	flag = false;
	// printf("word %s\n", word);
	while (word[i] != '\0' && type[i] == '1')
	{
		while (word[i] != '\0' && type[i] == '1' && \
			expand_is_str_in_char(ifs, word[i]))
			i++ ;
		printf("i %c\n", word[i]);
		printf("i %zu\n", i);
		while (word[i] != '\0' && type[i] == '1')
		{
			if (flag)
				return (true);
			if (expand_is_str_in_char(ifs, word[i]))
				break ;
			i++;
		}
		printf("i %s\n", ifs);
		printf("i %c\n", word[i]);
		printf("i %zu\n", i);
		flag = true;
	}
	return (false);
}

static size_t	get_not_quote_index(char *type, size_t i)
{
	if (token_set_flag_quote(type[i]) == DOUBLE_QUOTE_FLAG)
	{
		while (token_set_flag_quote(type[++i]) \
				!= DOUBLE_QUOTE_FLAG)
				;
		i++;
	}
	return (i);
}

bool	expand_is_ambiguous_error(char *redirect_word, \
									char *redirect_type, \
									char *ifs)
{
	size_t	i;

	if (redirect_word == NULL || redirect_type == NULL)
		return (true);
	i = 0;
	while (redirect_word[i] != '\0')
	{
		i = get_not_quote_index(redirect_word, i);
		if (expand_is_amb_error_unil(redirect_word, redirect_type, i, ifs))
			return (true);
		if (redirect_word[i] == '\0')
			break ;
		i++;
	}
	return (false);
}
