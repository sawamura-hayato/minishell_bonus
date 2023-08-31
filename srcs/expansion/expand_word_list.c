/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:32:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 18:16:26 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	expand_word_list(t_word_list **word_list, t_data *d)
{
	t_word_list	*node;
	char		*ifs;
	// bool		is_empty_ifs;

	node = *word_list;
	while (node != NULL)
	{
		if (node->tk_type == WORD && ft_strchr(node->word, '$'))
		{
			expand_variable_word_list(node, d);
			ifs = envs_get_value("IFS", d->envs_hashmap);
		printf("norm %s\n", node->word);
		printf("norm %s\n", node->type);
			// is_empty_ifs = expand_is_empty_ifs(ifs);
			// if (!is_empty_ifs && \
			// 	expand_is_word_splitting_word(node->word, node->type, ifs))
			// {
			// 	expand_word_splitting_word_list(node, ifs);
			// 	printf("node %p\n", node);
			// }
			free(ifs);
		}
		if (node->tk_type == WORD && \
			expand_is_delete_quotation_word(node->type))
		{
			expand_delete_quotation_word_list(node);
		}		node = node->next;
	}
}

// void	expand_variable_word_list(t_word_list *word_list, t_data *d)
// {
// 	char	*expand_word;

// 	expand_word = expand_get_expanded_token(word_list->word, d);
// 	word_list->word = expand_word;
// }

// void expand_variable_word_list(t_word_list **head, t_data *d)
// {
// 	t_word_list *node;

// 	node = expand_can_dollar_quote_string_word_list(head);
// 	while (node != NULL)
// 	{
// 		if (node->type == TK_SINGLE_QUOTE)
// 		{
// 			node = node->next;
// 			while (node->type != TK_SINGLE_QUOTE)
// 				node = node->next;
// 		}
// 		if (node->type == WORD && ft_strchr(node->word, '$'))
// 			expand_variable_word_list(node, d);
// 		node = node->next;
// 	}
// }
