/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_expanded_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:02:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/09 18:30:18 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	all_free(char *s1, char *s2);

static void	promote_type_pointer(char **type, char *s_word, char *e_word)
{
	while (s_word != e_word)
	{
		(*type)++;
		s_word++;
	}
}

void	expand_get_joined(char **expand, char **join_word,
							char **join_type, bool is_expand)
{
	char	*type;

	type = token_get_type_word(*expand, is_expand);
	*join_word = try_strjoin_free(*join_word, *expand);
	*join_type = try_strjoin_free(*join_type, type);
	free(*expand);
	*expand = NULL;
	free(type);
}

char	*expand_get_expand_word(char **word, t_envs **envs)
{
	char	*target_word;
	char	*target_value;

	target_word = expand_get_string_to_dollar_or_symbol(word);
	target_value = envs_get_value(target_word, envs);
	free(target_word);
	target_word = NULL;
	return (target_value);
}

char	*expand_convert_dollar_word(char **word, char **type, t_data *d)
{
	char	*expand_word;
	char	*tmp_word;
	t_quote	f_quote;

	tmp_word = *word;
	expand_word = *word;
	(*word)++;
	f_quote = token_set_flag_quote((*word)[0]);
	if (**word == '\0' || **word == '$')
		return (try_strdup("$"));
	if (f_quote == SINGLE_QUOTE_FLAG || f_quote == DOUBLE_QUOTE_FLAG)
		expand_word = expand_get_delete_dollar_quote(word, f_quote);
	else if (**word == '?')
		expand_word = expand_get_exit_status(word, d->exit_status);
	else
		expand_word = expand_get_expand_word(word, d->envs_hashmap);
	promote_type_pointer(type, tmp_word, *word);
	return (expand_word);
}

void	expand_get_expanded_token(char **token, char **type, t_data *d)
{
	char	*tmp;
	char	*tmp_type;
	char	*join_word;
	char	*join_type;
	char	*expand_word;

	join_word = NULL;
	join_type = NULL;
	tmp = *token;
	tmp_type = *type;
	while (*tmp != '\0')
	{
		if (*tmp == '$')
		{
			expand_word = expand_convert_dollar_word(&tmp, &tmp_type, d);
			expand_get_joined_str(&join_word, &join_type, expand_word);
			free(expand_word);
		}
		else
			expand_get_joined_str_to_dollar(&join_word, &join_type, \
												&tmp, &tmp_type);
	}
	all_free(*token, *type);
	*token = join_word;
	*type = join_type;
}
