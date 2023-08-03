/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:18:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/03 18:05:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "libft.h"

// 先頭ポインタが空白、タブ、改行、特殊文字の場合
size_t	token_can_next_token_index(const char *line, t_quote f_quote, \
										size_t index)
{
	if (f_quote == DEFAULT && (ft_isspace(*line) || ft_is_meta_char(*line)))
		index ++;
	return (index);
}

// size_t	token_get_current_word_size(char *line, t_quote f_quote)
// {
// 	return ();
// }

t_token	*token_get_current_token(char **line, t_quote f_quote, size_t *index)
{
	t_token		*current_token;
	size_t		size;
	char		*word;
	t_token_type	token_type;

	//構造体token作成(先頭ポインタが空白、タブ、改行、特殊文字の場合かつクウォートフラグがない場合によってindex発行)
	*index = token_can_next_token_index(*line, f_quote, *index);
	//入力プロンプトから分割したい文字列のサイズを出力する関数
	size = token_get_current_word_size(*line, f_quote);
	//3のサイズを使用して分割した文字列を出力する関数
	word = token_get_current_word(*line, size);
	token_type = get_token_type(word);
	current_token = create_token(word, token_type, *index);
	line += size;
	return (current_token);
}