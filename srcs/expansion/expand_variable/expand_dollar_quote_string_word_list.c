/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_quote_string_word_list.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:51:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/25 22:15:16 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char *expand_get_delete_dollar_quote(char **word, t_quote f_quote, t_data *d)
{
	char *expand_word;
	size_t size;
	size_t i;

	(*word)++;
	size = 0;
	while (f_quote != token_set_flag_quote((*word)[size]))
		size++;
	expand_word = try_calloc(size + 1, sizeof(char));
	i = 0;
	while (i < size)
	{
		expand_word[i] = (*word)[i];
		i++;
	}
	(*word) += size + 1;
	if (expand_is_variable_word(expand_word) && f_quote == DOUBLE_QUOTE_FLAG)
		expand_word = expand_get_expanded_token(expand_word, d);
	return (expand_word);
}

// void expand_dollar_quote_string_word_list(t_word_list *head)
// {
// 	t_word_list *node;
// 	size_t f_quote;
// 	size_t i;
// 	size_t size;

// 	node = head;
// 	i = 0;
// 	size = 0;
// 	while (node->word[i] != '\0')
// 	{
// 		if (node->word[i] == '$')
// 		{
// 			f_quote = node->type[++i] - '0';
// 			if (f_quote == IS_SINGLE_QUOTED ||
// 				f_quote == DOUBLE_QUOTE_FLAG)
// 			{
// 				while (f_quote != node->type[++i] - '0')
// 					size++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (false);
// }

// bool expand_is_dollar_quote_string_word_list(t_word_list *head)
// {
// 	t_word_list *node;
// 	size_t f_quote;
// 	size_t i;

// 	node = head;
// 	i = 0;
// 	while (node->word[i] != '\0')
// 	{
// 		if (node->word[i] == '$')
// 		{
// 			f_quote = node->type[++i] - '0';
// 			if (f_quote == IS_SINGLE_QUOTED ||
// 				f_quote == DOUBLE_QUOTE_FLAG)
// 				return (true);
// 		}
// 		i++;
// 	}
// 	return (false);
// }

// void expand_can_dollar_quote_string_word_list(t_word_list *head)
// {
// 	if (expand_is_dollar_quote_string_word_list(head))
// 		expand_dollar_quote_string_word_list(head);
// }

// "$'echo'echo$'echo'"
// "020000200000200002"

// "echo"
// "echo$'echo'"

// "echoecho"
// "$'echo'"

// "echoechoecho"
// "000000000000"

// echo $"ec   c"
// ec   c
