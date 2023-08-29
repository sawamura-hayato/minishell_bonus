/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_delete_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:39:09 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/28 15:21:20 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	word_list_delete_target_type(t_word_list *word_list, t_token_type taget);
void	redirect_list_delete_target_type(t_word_list *word_list, t_token_type taget);

// クウォートがあるかどうか確認する(番号)
//　当たっら削除する

static bool	is_type_quotation(int type)
{
	if (type == IS_SINGLE_QUOTED || type == IS_DOUBLE_QUOTED)
		return (true);
	return (false);
}

static size_t	expand_get_size_delete_quotation_word(char *word)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (word[i] != '\0')
	{
		if (!is_type_quotation(word[i] - '0'))
			size++;
		i++;
	}
	return (size);
}

bool	expand_is_delete_quotation_word(char *word)
{
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0')
	{
		if (is_type_quotation(word[i] - '0'))
			return (true);
		i++;
	}
	return (false);
}

void	expand_delete_quotation_word_list(t_word_list *word_list)
{
	char	*new_word;
	char	*new_type;
	size_t	i;
	size_t	new_index;

	new_word = try_calloc(expand_get_size_delete_quotation_word(word_list->type) + 1, sizeof(char));
	new_type = try_calloc(expand_get_size_delete_quotation_word(word_list->type) + 1, sizeof(char));
	i = 0;
	new_index = 0;
	// printf("old word %s\n", word_list->word);
	// printf("old type %s\n", word_list->type);
	while (word_list->type[i] != '\0')
	{
		if (!is_type_quotation(word_list->type[i] - '0'))
		{
			// printf("c %c\n", word_list->word[i]);
			// printf("c %c\n", new_word[new_index]);
			// printf("c %c\n", new_type[new_index]);
			new_word[new_index] = word_list->word[i];
			new_type[new_index] = word_list->type[i];
			new_index++;
		}
		i++;
	}
	// free(word_list->word);
	// exit(0);
	// free(word_list->type);
	word_list->word = new_word;
	word_list->type = new_word;
	// printf("new word %s\n", new_word);
	// printf("new type %s\n", new_type);
}

void	expand_delete_quotation_redirect_list(t_redirect_list *redirect_list)
{
	char	*new_word;
	char	*new_type;
	size_t	i;
	size_t	new_index;

	new_word = try_calloc(expand_get_size_delete_quotation_word(redirect_list->type) + 1, sizeof(char));
	new_type = try_calloc(expand_get_size_delete_quotation_word(redirect_list->type) + 1, sizeof(char));
	i = 0;
	new_index = 0;
	while (redirect_list->type[i] != '\0')
	{
		if (!is_type_quotation(redirect_list->type[i] - '0'))
		{
			printf("c %c\n", redirect_list->word[i]);
			new_word[new_index] = redirect_list->word[i];
			printf("c %c\n", new_word[new_index]);
			new_type[new_index] = redirect_list->type[i];
			printf("c %c\n", new_type[new_index]);
			new_index++;
		}
		i++;
	}
	// printf("old word %s\n", redirect_list->word);
	// printf("old type %s\n", redirect_list->type);
	// free(redirect_list->word);
	// free(redirect_list->type);
	redirect_list->word = new_word;
	redirect_list->type = new_word;
	// printf("new word %s\n", new_word);
	// printf("new type %s\n", new_type);
}

// void	expand_delete_quotation_word_list(t_word_list *word_list)
// {
// 	expand_delete_quotation_word_list(word_list);
// }

// void	expand_delete_quotation_redirect_list(t_redirect_list *redirect_list)
// {
// 	expand_delete_quotation_word_list(redirect_list);
// }
