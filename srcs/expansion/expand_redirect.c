/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:35:33 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/03 09:47:14 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*expand_convert_dollar_word_delimiter(char **word, t_data *d)
{
	char	*expand_word;

	expand_word = *word;
	(*word)++;
	if (**word == '\0')
		return (try_strdup(expand_word));
	if (**word == '?')
		expand_word = expand_get_exit_status(word, d->exit_status);
	else
		expand_word = expand_get_expand_word(word, d->envs_hashmap);
	return (expand_word);
}

static void	expand_get_expanded_word_delimiter(char **token, \
												char **type, \
												t_data *d)
{
	char	*expand;
	char	*tmp;
	char	*tmp_type;
	char	*join_word;
	char	*join_type;

	join_word = NULL;
	join_type = NULL;
	tmp = *token;
	tmp_type = *type;
	while (*tmp != '\0')
	{
		if (*tmp == '$')
		{
			expand = expand_convert_dollar_word_delimiter(&tmp, d);
			expand_get_joined(&expand, &join_word, &join_type, true);
		}
		else
		{
			expand = expand_get_str_to_dollar(&tmp, &tmp_type);
			expand_get_joined(&expand, &join_word, &join_type, false);
		}
	}
	free(*token);
	free(*type);
	*token = join_word;
	*type = join_type;
}

void	expand_redirect_list(t_redirect_list **redirect_list, t_data *d)
{
	t_redirect_list	*node;

	node = *redirect_list;
	while (node != NULL)
	{
		if (node->re_type == PS_FILE && ft_strchr(node->word, '$'))
		{
			expand_variable_redirect_list(node, d);
		}
		else if (node->re_type == PS_DELIMITER && ft_strchr(node->word, '$'))
			expand_get_expanded_word_delimiter(&(node->word), &(node->type), d);
		if (node->re_type == PS_FILE && \
			expand_is_delete_quotation_word(node->type))
			expand_delete_quotation_redirect_list(node);
		node = node->next;
	}
}
