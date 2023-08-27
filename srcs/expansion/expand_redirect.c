/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:35:33 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/27 18:41:23 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	expand_redirect_list(t_redirect_list **redirect_list, t_data *d)
{
	t_redirect_list *node;

	node = *redirect_list;
	while (node != NULL)
	{
		if (node->re_type == PS_FILE && ft_strchr(node->word, '$'))
		{
			expand_variable_redirect_list(node, d);
			// expand_word_splitting_redirect_list(node, d);
			// expand_filename(node);
			// expand_delete_quotation(node);
		}
		else if (node->re_type == PS_DELIMITER && ft_strchr(node->word, '$'))
		{
			//単純な展開クウォート削除も行わない関数作成
		}
		// exit(0);
		node = node->next;
	}
}

// bool expand_is_tokens(char *expand_word)
// {
// 	bool f_space;

// 	f_space = false;
// 	while (*expand_word != '\0')
// 	{
// 		if (f_space)
// 			return (true);
// 		if (ft_isspace(*expand_word))
// 			f_space = true;
// 		expand_word++;
// 	}
// 	return (false);
// }

// void expand_token_redirect_list(t_redirect_list *redirect_list, t_data *d, t_redirect_type is_quote)
// {
// 	char *expand_word;

// 	expand_word = expand_get_expanded_token(redirect_list->word, d);
// 	// 環境変数がない場合, トークンが複数に分かれる場合
// 	if (is_quote != PS_REDIRECT_DOUBLE_QUOTE &&
// 		(expand_word == NULL || expand_is_tokens(expand_word)))
// 	{
// 		free(expand_word);
// 		// token->is_abm_error = true;
// 	}
// 	else
// 	{
// 		// free(redirect_list->word);
// 		redirect_list->word = expand_word;
// 	}
// }

// void expand_variable_redirect_list(t_redirect_list *head, t_data *d)
// {
// 	t_redirect_list *node;

// 	node = expand_can_dollar_quote_string_redirect(&head);
// 	while (node != NULL)
// 	{
// 		if (node->re_type == TOKEN_SINGLE_QUOTE)
// 		{
// 			node = node->next;
// 			while (node->re_type != TOKEN_SINGLE_QUOTE)
// 				node = node->next;
// 		}
// 		if (node->type != TOKEN_SINGLE_QUOTE && ft_strchr(node->word, '$'))
// 			expand_token_redirect_list(node, d, node->re_type);
// 		node = node->next;
// 	}
// }