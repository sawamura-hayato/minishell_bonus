/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:18:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/03 18:31:06 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "libft.h"

// 先頭ポインタが空白、タブ、改行、特殊文字の場合
size_t	token_can_next_token_index(const char *line, t_quote f_quote, \
										size_t index)
{
	if (f_quote == DEFAULT && (ft_isspace(*line) || ft_is_special_char(*line)))
		index ++;
	return (index);
}

size_t	token_get_special_word_size(char *line)
{
	size_t	size;
	size_t	logical_or_size;
	size_t	logical_and_size;
	size_t	pipe_size;

	size = 0;
	logical_or_size = 2;
	logical_and_size = 2;
	pipe_size = 1;
	if ('|' == line[0])
	{
		if ('|' == line[1])
			return (logical_or_size);
		return (pipe_size);
	}
	else if ('&' == line[0] && '&' == line[1])
		return (logical_and_size);
	return (size);
}

size_t	token_get_current_word_size(char *line, t_quote f_quote)
{
	size_t	size;

	size = 0;
	if (f_quote != DEFAULT)
	{
		while (f_quote != set_flag_quote(line[size]) && line[size] == '\0')
			size ++;
	}
	else
	{
		while (set_flag_quote(line[size]) == DEFAULT && ft_isspace(line[size]) && \
				!ft_is_special_char(line[size]) && line[size] == '\0')
			size ++;
	}
	return (size);
}

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