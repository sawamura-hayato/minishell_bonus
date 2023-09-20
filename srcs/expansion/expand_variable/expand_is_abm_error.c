/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_is_abm_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:01:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/20 12:11:19 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	ft_is_c_in_str(char *str, char c);

static bool	free_de_ifs_boolean(char *de_ifs, bool boolean)
{
	free(de_ifs);
	return (boolean);
}

static bool	expand_is_amb_error_unil(char *w, char *t, size_t i, char *ifs)
{
	bool	flag;
	char	*de_ifs;

	flag = false;
	de_ifs = expand_check_ifs_default_char(ifs);
	while (w[i] != '\0' && t[i] == IS_SUBSTITUTED)
	{
		while (w[i] != '\0' && t[i] == '1' && ft_is_c_in_str(ifs, w[i]))
		{
			if (flag && !ft_is_c_in_str(de_ifs, w[i]))
				return (free_de_ifs_boolean(de_ifs, flag));
			else if (!ft_is_c_in_str(de_ifs, w[i++]))
				flag = true;
		}
		while (w[i] != '\0' && t[i] == IS_SUBSTITUTED)
		{
			if (flag)
				return (free_de_ifs_boolean(de_ifs, flag));
			if (ft_is_c_in_str(ifs, w[i++]))
				break ;
		}
		flag = true;
	}
	return (free_de_ifs_boolean(de_ifs, false));
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
