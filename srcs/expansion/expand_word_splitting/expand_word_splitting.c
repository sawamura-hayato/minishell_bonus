/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:30:36 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/16 11:48:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char *envs_get_value(char *_key, t_envs **envs_hashmap);

// char *expand_get_splitting_word(char **word)
// {
// 	// "    aa bbbb"     aa
// 	// " bbbb"           bbbb
// 	// " ddd  ee  c  "   ddd
// 	// "  ee  c  "       ee
// 	// "  c  "           c
// 	// "  "              NULL
// }

// void expand_get_splitting_word_list(t_word_list **word_list)
// {
// 	t_word_list *new_word_list;
// 	char *tmp_word;
// 	char *splitting_word;

// 	tmp_word = (*word_list)->word;
// 	(*word_list)->word = expand_get_splitting_word(&tmp_word);
// 	while (*tmp_word)
// 	{
// 		splitting_word = expand_get_splitting_word(&tmp_word);
// 		if (splitting_word != NULL)
// 		{
// 			new_word_list = ast_init_word_node(splitting_word);
// 			(*word_list)->next = new_word_list;
// 			*word_list = (*word_list)->next;
// 		}
// 	}
// 	free(tmp_word);
// }

// void expand_splitting_word_list(t_word_list *word_list, char *ifs)
// {
// 	t_word_list *tmp_word_list;
// 	t_word_list *new_word_list;
// 	t_word_list *head;

// 	tmp_word_list = NULL;
// 	new_word_list = NULL;
// 	head = word_list;
// 	// IFSがデフォルトの場合
// 	if (expand_check_ifs_default_char(ifs->value) ||
// 		ft_strchr(ifs->value, ' ') ||
// 		ft_strchr(ifs->value, '\t'))
// 	{
// 		// 通常の変数展開後の場合空白、タブ、改行があったらトークンを分ける。
// 		while (word_list != NULL)
// 		{
// 			if (word_list->type == TOKEN_SINGLE_QUOTE || word_list->type == TOKEN_DOUBLE_QUOTE)
// 			{
// 				word_list = word_list->next;
// 				while (word_list->type == TOKEN_SINGLE_QUOTE || word_list->type == TOKEN_DOUBLE_QUOTE)
// 					word_list = word_list->next;
// 			}
// 			if (expand_is_check_space_word(word_list))
// 			{
// 				tmp_word_list = word_list->next;
// 				expand_get_splitting_word_list(&word_list);
// 				word_list->next = tmp_word_list;
// 			}
// 		}
// 	}
// 	// IFSが任意で設定されている場合
// 	word_list = head;
// 	while (word_list != NULL)
// 	{
// 		// 任意の文字があった場合空白にする
// 		expand_blank_word_if_ifs_char(word_list, ifs->value);
// 		word_list = word_list->next;
// 	}
// }

// void expand_splitting_redirect_list(t_redirect_list *redirect_list, char *ifs)
// {
// }

void expand_word_splitting(t_ast *node, t_data *d)
{
	char *ifs;
	bool is_empty_ifs;
	char *check_ifs_default_char;

	ifs = envs_get_value("IFS", d->envs_hashmap);
	is_empty_ifs = expand_is_empty_ifs(ifs);
	check_ifs_default_char = expand_check_ifs_default_char(ifs);
	// クウォートがある場合、IFS の値が空文字列の場合（IFS=, IFS='', IFS=""）
	if (expand_is_word_splitting_word_list(node->command_list->word_list, ifs) &&
		!is_empty_ifs)
		expand_splitting_word_list(&node->command_list->word_list, ifs, check_ifs_default_char);
	// if (expand_is_word_spliting_redirect_list(node->command_list->redirect_list) && \
	// 	!is_empty_ifs)
	// 	expand_splitting_redirect_list(&(node->command_list->redirect_list), ifs);
	// free(check_ifs_default_char);
}
