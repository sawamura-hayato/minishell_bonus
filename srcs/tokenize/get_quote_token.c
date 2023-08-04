/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:34:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/04 18:05:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdbool.h>
#include <stdio.h>

// 1. 入力プロンプトの先頭を見てクウォートかどうか判定する
// 現在のクウォートのフラグによって以下の場合わけがある

// 現在のクウォートのフラグがtrueかつ先頭がtrueの場合
// フラグをfalseにして現在のトークンを発行、クウォート分ポインタを動かし、1に戻る。
// 現在のクウォートのフラグがfalseかつ先頭がtrueの場合
// フラグをtrueにして現在のトークンを発行、クウォート分ポインタを動かし、1に戻る。
// 現在のクウォートのフラグがtrueかつ先頭がfalseの場合
// そのまま2を実行する
// 現在のクウォートのフラグがfalseかつ先頭がfalseの場合
// そのまま2を実行する

char	*get_quote_token(t_quote f_quote)
{
	if (SINGLE_QUOTE_FLAG == f_quote)
		return ("\'");
	else if (DOUBLE_QUOTE_FLAG == f_quote)
		return ("\"");
	return (NULL);
}

char	*skip_space_line(char *line)
{
	while (ft_isspace(*line))
	{
		printf("space %s\n", line);
		line++;
	}
	printf("space %s\n", line);
	return (line);
	// printf("space %c\n", *line);
}

bool	token_can_get_quote_token(t_token **head, char **line, \
										t_quote *f_quote, size_t index)
{
	t_quote	first_char;
	t_token *quote_token;

	first_char = set_flag_quote(*line[0]);
	if (*f_quote != DEFAULT && *f_quote == first_char)
	{
		*f_quote = DEFAULT;
		quote_token = create_token(get_quote_token(first_char), \
										set_flag_token(*line, DEFAULT), index);
		token_addback(head, quote_token);
		(*line)++;
		return (true);
	}
	else if (*f_quote == DEFAULT && first_char != DEFAULT)
	{
		*f_quote = first_char;
		quote_token = create_token(get_quote_token(first_char), \
										set_flag_token(*line, DEFAULT), index);
		token_addback(head, quote_token);
		(*line)++;
		return (true);
	}
	else if (**line == '\0')
		return (true);
	return (false);
}
