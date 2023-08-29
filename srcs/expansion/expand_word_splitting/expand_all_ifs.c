/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all_ifs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:26:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/21 14:15:46 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

if (expand_is_all_ifs(node->command_list->word_list->word, ifs, check_ifs_default_char))
	expand_splitting_word_list_all_ifs(node->command_list->word_list);

bool	expand_is_all_ifs(char *word, char *ifs)
{
	while (*word != '\0')
	{
		if (!expand_is_str_in_char(ifs, *word))
			return (false);
		word++;
	}
	return (true);
}

void	expand_splitting_word_list_by_all_ifs(t_word_list **word_list, char *ifs, char *ifs_default_char)
{
	size_t	i;
	char	*tmp;
	t_word_list *node;
	t_word_list *pre_node;
		// t_word_list	*tmp_node;

	i = 0;
	tmp = (*word_list)->word;
	if (expand_is_str_in_char((*word_list)->word[i], ifs))
		(*word_list)->word = debug_new_word_list(try_strdup(""), 0, WORD);
	node = *word_list;
	pre_node = NULL;
	while (node != NULL)
	{
		if (expand_is_word_splitting(node->word, ifs) &&
			node->is_expand)
		{
			printf("word_list \n");
			debug_printf_word_list(*word_list);
			if (*ifs_default_char != '\0')
				expand_splitting_word_list_by_ifs_default_char(&node, ifs_default_char);
			// node->word++;
			while (*(node->word) != '\0' && expand_is_str_in_char(ifs, *(node->word)))
			{
				if (pre_node == NULL)
				{
					word_list_new_tail(&pre_node, debug_new_word_list(try_strdup(""), 0, WORD));
					pre_node->next = (*word_list);
					(*word_list) = pre_node;
				}
				else
				{
					word_list_new_target(&pre_node, pre_node, debug_new_word_list(try_strdup(""), 0, WORD));
					// printf("word_list \n");
					// debug_printf_word_list(*word_list);
					// printf("pre_node \n");
					// debug_printf_word_list(pre_node);
					pre_node = pre_node->next;
				}
				node->word++;
			}
			expand_splitting_word_list_by_ifs_not_default_char(&node, ifs);
		}
		pre_node = node;
		node = node->next;
	}


}
