/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:30:36 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/20 11:34:54 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	ft_is_c_in_str(char *str, char c);

bool	expand_is_quoted(char *type, size_t size)
{
	size_t	i;
	bool	f_quote;

	i = 0;
	f_quote = false;
	while (i < size)
	{
		if (IS_DOUBLE_QUOTED == type[i])
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
	while (word[i] != '\0' && !ft_is_c_in_str(ifs, word[i]))
		i++;
	if (word[i] == '\0')
		return (false);
	return (true);
}

char	*expand_get_ifs(t_envs **envs)
{
	char	*ifs;

	ifs = envs_get_value("IFS", envs);
	if (ifs == NULL)
		ifs = try_strdup(" \t\n");
	return (ifs);
}
