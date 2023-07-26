/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:16 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/26 12:22:05 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"

t_token	*tokenize(char *line)
{
	t_token	*token_head;
	// t_token	*token;
	// char	*word;
	size_t	i;

	token_head = NULL;
	i = 0;
	while (line[i] != NULL_CHAR)
	{
		// while (ft_isspace(line[i]) || line[i] != NULL_CHAR)
		// 	i++;
		//クウォートがある場合
		//クウォート判定(start)
		//判定したクウォート探索する関数(end)
		//文字列index(start~end)を作成する関数
		// if (line[i] == SINGLE_QUOTE || line[i] == DOUBLE_QUOTE)
		// {
		// 	while (line[i] != NULL_CHAR || line[i] == SINGLE_QUOTE || line[i] == DOUBLE_QUOTE)
		// 	{
		// 		if ()
		// 	}
		// }
		//通常の場合
		//探索前(start)
		//空白もしくは終端文字になるまでoperator, redirectを探索する関数（end）
		//先頭にoperator、redirectの場合最大2連続を探索する関数(end)

		//空白の場合（一つ以上空白がある場合）
		//トークンの分け目になる（ただしクウォート以外の場合）
		i++;
	}
	return (token_head);
}
