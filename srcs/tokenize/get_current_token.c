/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:18:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/05 18:10:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "tokenize.h"

size_t	token_can_next_token_index(t_token *head, char **line, t_quote f_quote, \
										size_t index)
{
	size_t	i;
	bool	flag;
	t_token_type	end_token_type;

	i = 0;
	flag = true;
	end_token_type = token_last_token_type(head);
	if (f_quote == DEFAULT && (ft_isspace((*line)[i]) || ft_is_special_char((*line)[i])))
	{
		index ++;
		flag = false;
		while (ft_isspace((*line)[i]))
			i++;
	}
	*line += i; 
	if (flag && token_is_a_control_char(end_token_type))
		index++;
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
	else if ('&' == line[0])
	{
		if ('&' == line[1])
			return (logical_and_size);
		return (++size);
	}
	return (size);
}

size_t	token_get_current_word_size(char *line, t_quote f_quote)
{
	size_t	size;

	size = token_get_special_word_size(line);
	if (f_quote != DEFAULT)
	{
		while (f_quote != set_flag_quote(line[size]) && line[size] != '\0')
			size ++;
	}
	else
	{
		// size = token_get_special_word_size(line);
		while (set_flag_quote(line[size]) == DEFAULT && !ft_isspace(line[size]) && \
				!ft_is_special_char(line[size]) && line[size] != '\0')
			size ++;
	}
	// printf("spcae line  %s\n", line);
	return (size);
}

char	*token_get_current_word(char *line, size_t size)
{
	size_t	i;
	char	*word;

	printf("line %s, size %zu\n", line, size);
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

bool	token_is_a_control_char(t_token_type token_type)
{
	if (token_type == LOGICAL_AND || token_type == LOGICAL_OR || token_type == PIPE)
		return (true);
	return (false);
}

void	token_get_current_token(t_token **head, char **line, \
									t_quote f_quote, size_t *index)
{
	t_token		*current_token;
	size_t		size;
	char		*word;
	t_token_type	current_token_type;

	//構造体token作成(先頭ポインタが空白、タブ、改行、特殊文字の場合かつクウォートフラグがない場合によってindex発行)
	//入力プロンプトから分割したい文字列のサイズを出力する関数
	size = token_get_current_word_size(*line, f_quote);
	// printf("current line %s, size %zu\n", *line, size);
	//3のサイズを使用して分割した文字列を出力する関数
	word = token_get_current_word(*line, size);
	current_token_type = set_flag_token(word, f_quote);
	current_token = create_token(word, current_token_type, *index);
	token_addback(head, current_token);
	*line += size;
}

//echo "|| &&" 