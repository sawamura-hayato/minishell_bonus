/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:32:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/29 23:03:50 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ft_substr(char const *s, unsigned int start, size_t end);
char	*try_strdup(const char *s1);
// void	expand_word_splitting_word_list(t_word_list *word_list, t_data *d, char *ifs)
// {
// 	char	*ifs_default_char;
// 	size_t	i;

// 	if (word_list->word == NULL || word_list->type == NULL)
// 		return (false);
// 	ifs_default_char = expand_check_ifs_default_char(ifs);
// 	i = 0;
// 	while (word_list->word[i] != '\0')
// 	{
// 		while (word_list->type[i] != '\0')
// 		{
// 			if (IS_DOUBLE_QUOTED == (word_list->type[i] - '0'))
// 			{
// 				i++;
// 				while (IS_DOUBLE_QUOTED != (word_list->type[i] - '0'))
// 					i++;
// 			}
// 			else
// 			{
				
// 			}
// 			i++;
// 		}
// 		while (word_list->word[i] != '\0' && word_list->type[i] == '1')
// 		{
// 			while (word_list->word[i] != '\0' && word_list->type[i] == '1' && expand_is_str_in_char(ifs, word_list->word[i]))
// 			{
// 				if (expand_is_str_in_char(ifs_default_char, word_list->word[i]))
// 				{
// 					i++;
// 					continue;
// 				}
// 				else
// 					return (true);
// 			}
// 			while (word_list->word[i] != '\0' && word_list->type[i] == '1')
// 			{
// 				if (!expand_is_str_in_char(ifs, word_list->word[i]))
// 				{
// 					i++;
// 					continue;
// 				}
// 				else
// 					return (true);
// 			}
// 		}
// 		if (word_list->word[i] == '\0')
// 			break;
// 		i++;
// 	}
// 	return (false);
// }

// char	*expand_get_type_word_copy(char *word)

// 文字列＋環境変数
// 文字列　NULL ->先頭の処理かく
//        それ以外はwhile

// ifs（通常の場合かつ展開後の値）が来るまでので文字列を取得
// 

// char	 expand_get_str_to_ifs(char **word, char **type char *ifs)
// {
// }


// echo->
// echo->
// // "ddd"$A
// "ddd"->out->ls
t_word_list	*expand_new_word_list(t_word_list *node, size_t i, t_word_list *next_node)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	i++;
	new_word_list->word = try_strdup(&(node->word[i]));
	new_word_list->type = try_strdup(&(node->type[i]));
	new_word_list->tk_type = WORD;
	new_word_list->next = next_node;
    return (new_word_list);
}

t_word_list	*expand_new_null_word_list(t_word_list *next_node)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	new_word_list->word = try_strdup("");
	new_word_list->type = NULL;
	new_word_list->tk_type = WORD;
	new_word_list->next = next_node;
	return (new_word_list);
}
// static bool	is_ifs(word[i])
bool	expand_is_quoted(char *type, size_t size)
{
	size_t	i;
	bool	f_quote;

	i = 0;
	f_quote = false;
	while (i < size)
	{
		if (IS_DOUBLE_QUOTED == type[i] - '0')
			f_quote = !f_quote;
		i++;
	}
	return (f_quote);
}

bool	expand_have_ifs(char *word, char *ifs)
{
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0' && !expand_is_str_in_char(ifs, word[i]))
		i++;
	if (word[i] == '\0')
		return (false);
	return (true);
}

void	expand_word_splitting_word_list(t_word_list *node, char *ifs)
{
	t_word_list	*word_list;
	size_t		i;
	char		*ifs_default_char;

	i = 0;
	word_list = node;
	while (word_list->word[i] != '\0')
	{
		if (expand_is_str_in_char(ifs, word_list->word[i]) && !expand_is_quoted(word_list->type, i) && word_list->type[i] == '1')
		{
			ifs_default_char = expand_check_ifs_default_char(ifs);
			if (i == 0)
			{
				while (word_list->word[i] != '\0' && !expand_is_str_in_char(ifs, word_list->word[i]))
				{
					if (!expand_is_str_in_char(ifs_default_char, word_list->word[i]))
						word_list->next = expand_new_null_word_list(word_list->next);
					i++;
				}
			}
			else
			{
				word_list->next = expand_new_word_list(word_list, i, word_list->next);
				word_list->word = ft_substr(word_list->word, 0, i);
				word_list->type = ft_substr(word_list->type, 0, i);
			}
			break;
		}
		i++;
	}
	if (expand_have_ifs(word_list->next->word, ifs))
		expand_word_splitting_word_list(word_list->next, ifs);
}

void	expand_word_list(t_word_list **word_list, t_data *d)
{
	// t_word_list *pre_node;
	t_word_list *node;
	char		*ifs;
	bool is_empty_ifs;

	node = *word_list;
	while (node != NULL)
	{
		if (node->tk_type == WORD && ft_strchr(node->word, '$'))
		{
			expand_variable_word_list(node, d);
			// word_splittingできるかどうかチェックする関数
			ifs = envs_get_value("IFS", d->envs_hashmap);
			is_empty_ifs = expand_is_empty_ifs(ifs);
			if (!is_empty_ifs && expand_is_word_splitting_word_list(node, ifs))
			{
				// t_word_list
// // echo -> "ddd"$A -> aad -> word
//         -> "ddd"->out->ls -> add
				printf("ok   %s\n", node->word);
				expand_word_splitting_word_list(node, ifs);
				
			}
			if (expand_is_delete_quotation_word(node->type))
				expand_delete_quotation_word_list(node);
		}
		node = node->next;
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
