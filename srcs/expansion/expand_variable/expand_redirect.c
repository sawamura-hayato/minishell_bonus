/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:35:33 by hsawamur          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/22 13:24:05 by hsawamur         ###   ########.fr       */
=======
/*   Updated: 2023/08/15 16:59:58 by hsawamur         ###   ########.fr       */
>>>>>>> 106-単語分割
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool expand_is_tokens(char *expand_word)
{
	bool f_space;

	f_space = false;
	while (*expand_word != '\0')
	{
		if (f_space)
			return (true);
		if (ft_isspace(*expand_word))
			f_space = true;
		expand_word++;
	}
	return (false);
}

<<<<<<< HEAD
void expand_token_redirect_list(t_redirect_list *redirect_list, t_data *d, t_redirect_list_type is_quote)
=======
void expand_token_redirect_list(t_redirect_list *redirect_list, t_data *d, t_redirect_type is_quote)
>>>>>>> 106-単語分割
{
	char *expand_word;

	expand_word = expand_get_expanded_token(redirect_list->word, d);
	// 環境変数がない場合, トークンが複数に分かれる場合
<<<<<<< HEAD
	if (is_quote != TOKEN_DOUBLE_QUOTE &&
=======
	if (is_quote != PS_REDIRECT_DOUBLE_QUOTE &&
>>>>>>> 106-単語分割
		(expand_word == NULL || expand_is_tokens(expand_word)))
	{
		free(expand_word);
		// token->is_abm_error = true;
	}
	else
	{
		// free(redirect_list->word);
		redirect_list->word = expand_word;
	}
}

void expand_variable_redirect_list(t_redirect_list **head, t_data *d)
{
	t_redirect_list *node;

	node = expand_can_dollar_quote_string_redirect(head);
	while (node != NULL)
	{
<<<<<<< HEAD
		if (node->type == TOKEN_SINGLE_QUOTE)
		{
			node = node->next;
			while (node->type != TOKEN_SINGLE_QUOTE)
				node = node->next;
		}
		if (node->type != TOKEN_SINGLE_QUOTE && ft_strchr(node->word, '$'))
=======
		if (node->type == PS_REDIRECT_SINGLE_QUOTE)
		{
			node = node->next;
			while (node->type != PS_REDIRECT_SINGLE_QUOTE)
				node = node->next;
		}
		if (node->type != PS_REDIRECT_SINGLE_QUOTE && ft_strchr(node->word, '$'))
>>>>>>> 106-単語分割
			expand_token_redirect_list(node, d, node->type);
		node = node->next;
	}
}