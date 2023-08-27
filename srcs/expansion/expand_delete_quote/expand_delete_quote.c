/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_delete_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:39:09 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/27 21:01:45 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	word_list_delete_target_type(t_word_list *word_list, t_token_type taget);
void	redirect_list_delete_target_type(t_word_list *word_list, t_token_type taget);

// クウォートがあるかどうか確認する(番号)
//　当たっら削除する

static size_t    get_size(char *word)
{
    size_t    count;

    count = 0;
    while (*word != '\0')
    {
        if (is_quotation(*word) == false)
            count++;
        word++;
    }
    return (count);
}

void    expand_delete_quotation_redirect_list(t_redirect_list *delimiter)
{
    char    *old_delimiter;
    char    *new_delimiter;
    size_t    i;

    old_delimiter = delimiter->word;
    new_delimiter = try_calloc(get_size(delimiter->word) + 1, sizeof(char));
    i = 0;
    while (*old_delimiter != '\0')
    {
        if (is_quotation(*old_delimiter) == false)
        {
            new_delimiter[i] = *old_delimiter;
            i++;
        }
        old_delimiter++;
    }
    free(delimiter->word);
    delimiter->word = new_delimiter;
    // printf("%s\n", new_delimiter);
}

void	expand_delete_quotation_word_list(t_word_list *word_list)
{
	
	word_list_delete_target(word_list, SINGLE_QUOTE);
	word_list_delete_target(word_list, DOUBLE_QUOTE);
	word_list_strjoin(word_list);
}

void	expand_delete_quotation_redirect_list(t_redirect_list *redirect_list)
{
	redirect_list_delete_target(redirect_list, SINGLE_QUOTE);
	redirect_list_delete_target(redirect_list, DOUBLE_QUOTE);
	redirect_list_strjoin(redirect_list);
}
