/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_is_abm_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:01:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/20 05:38:57 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	ft_is_str_in_c(char *str, char c);

static bool	expand_is_amb_error_unil(char *word, char *type, \
										size_t i, char *ifs)
{
	bool	flag;

	flag = false;
	while (word[i] != '\0' && type[i] == '1')
	{
		while (word[i] != '\0' && type[i] == '1' && \
			ft_is_str_in_c(ifs, word[i]))
			i++ ;
		while (word[i] != '\0' && type[i] == '1')
		{
			if (flag)
				return (true);
			if (ft_is_str_in_c(ifs, word[i]))
				break ;
			i++;
		}
		flag = true;
	}
	return (false);
}

static size_t	get_not_quote_index(char *type, size_t i)
{
	if (IS_DOUBLE_QUOTED == type[i])
	{
		i++;
		while (type[i] != '\0' && IS_DOUBLE_QUOTED != type[i])
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
		i = get_not_quote_index(redirect_type, i);
		if (expand_is_amb_error_unil(redirect_word, redirect_type, i, ifs))
			return (true);
		if (redirect_type[i] == '\0')
			break ;
		i++;
	}
	return (false);
}
