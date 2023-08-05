/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:34:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/02 12:18:08 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdbool.h>

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

t_quote	set_flag_quote(char quote)
{
	if (SINGLE_QUOTE == quote)
		return (SINGLE_QUOTE_FLAG);
	else if (DOUBLE_QUOTE == quote)
		return (DOUBLE_QUOTE_FLAG);
	return (DEFAULT);
}

char	*get_quote_token(t_quote f_quote)
{
	if (SINGLE_QUOTE_FLAG == f_quote)
		return ("\'");
	else if (DOUBLE_QUOTE_FLAG == f_quote)
		return ("\"");
	return (NULL);
}

bool	token_can_get_quote_token(t_token **token, const char **prompt, \
										t_quote *f_quote, size_t index)
{
	t_quote	first_char;
	// t_token *quote_token;

	first_char = set_flag_quote(*prompt[0]);
	(void)token;
	(void)index;
	if (*f_quote != DEFAULT && *f_quote == first_char)
	{
		*f_quote = DEFAULT;
		(*prompt)++;
		// quote_token = create_token(get_quote_token(f_quote), WORD, index);
		// token_addback(&head, quote_token);
		return (true);
	}
	else if (first_char != DEFAULT)
	{
		*f_quote = first_char;
		(*prompt)++;
		// quote_token = create_token(get_quote_token(f_quote), WORD, index);
		// token_addback(&head, quote_token);
		return (true);
	}
	return (false);
}