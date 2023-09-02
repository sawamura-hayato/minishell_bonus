/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:35:33 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/02 16:42:08 by tterao           ###   ########.fr       */
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
	char	*join_word;
	char	*join_type;

	join_word = NULL;
	join_type = NULL;
	tmp = *token;
	while (*tmp != '\0')
	{
		if (*tmp == '$')
		{
			expand = expand_convert_dollar_word_delimiter(&tmp, d);
			expand_get_joined(&expand, &join_word, &join_type, true);
		}
		else
		{
			expand = expand_get_str_to_dollar(&tmp);
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
	char			*ifs;
	bool			is_empty_ifs;

	node = *redirect_list;
	while (node != NULL)
	{
		if (node->re_type == PS_FILE && ft_strchr(node->word, '$'))
		{
			expand_variable_redirect_list(node, d);
			ifs = envs_get_value("IFS", d->envs_hashmap);
			is_empty_ifs = expand_is_empty_ifs(ifs);
			if (!node->is_ambiguous_error && \
			!is_empty_ifs && \
			expand_is_word_splitting_word(node->word, node->type, ifs))
				expand_word_splitting_redirect_list(node, ifs);
			free(ifs);
		}
		else if (node->re_type == PS_DELIMITER && ft_strchr(node->word, '$'))
			expand_get_expanded_word_delimiter(&(node->word), &(node->type), d);
		if (node->re_type == PS_FILE && \
			expand_is_delete_quotation_word(node->type))
			expand_delete_quotation_redirect_list(node);
		node = node->next;
	}
}
