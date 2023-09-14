/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_is_word_splitting.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:16:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/14 14:34:02 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

#define SPACE ' '
#define TAB '\t'
#define NEW_LINE '\n'

bool	expand_is_word_splitting(char *word, char *type, char *ifs, size_t i)
{
	size_t	j;

	j = 0;
	if (type == NULL || ifs == NULL)
		return (false);
	while (type[i] != '\0' && IS_SUBSTITUTED == type[i])
	{
		while (ifs[j] != '\0')
		{
			if (IS_SUBSTITUTED == type[i] && \
				ifs[j] == word[i])
				return (true);
			j++;
		}
		j = 0;
		i++;
	}	
	return (false);
}

bool	expand_is_word_splitting_word(char *word, char *type, char *ifs)
{
	size_t	i;

	i = 0;
	if (type == NULL)
		return (false);
	while (type[i] != '\0')
	{
		if (IS_DOUBLE_QUOTED == type[i])
		{
			while (IS_DOUBLE_QUOTED != type[++i])
			{
				if (type[i] == '\0')
					return (false);
			}
		}
		else
		{
			if (expand_is_word_splitting(word, type, ifs, i))
				return (true);
		}
		i++;
	}
	return (false);
}

bool	expand_is_empty_ifs(char *ifs)
{
	if (ifs == NULL || ifs[0] == '\0')
		return (true);
	return (false);
}

char	*expand_set_ifs_default_char(int f_space, int f_tab, int f_new_line)
{
	char	*ifs_default_char;
	char	*tmp;
	size_t	size;

	size = f_space + f_tab + f_new_line;
	ifs_default_char = try_calloc(size + 1, sizeof(char));
	tmp = ifs_default_char;
	if (f_space)
	{
		*tmp = SPACE;
		tmp++;
	}
	if (f_tab)
	{
		*tmp = TAB;
		tmp++;
	}
	if (f_new_line)
	{
		*tmp = NEW_LINE;
		tmp++;
	}
	return (ifs_default_char);
}

char	*expand_check_ifs_default_char(char *ifs)
{
	int	f_space;
	int	f_tab;
	int	f_new_line;

	f_space = 0;
	f_tab = 0;
	f_new_line = 0;
	if (ifs == NULL)
		return (try_strdup(""));
	while (*ifs != '\0')
	{
		if (*ifs == SPACE)
			f_space = 1;
		if (*ifs == TAB)
			f_tab = 1;
		if (*ifs == NEW_LINE)
			f_new_line = 1;
		ifs++;
	}
	return (expand_set_ifs_default_char(f_space, f_tab, f_new_line));
}
