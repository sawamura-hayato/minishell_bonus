/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:16 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/27 17:35:35 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "libft.h"
#include <stdlib.h>

typedef enum e_quote {
	DEFAULT,
	SINGLE_QUOTE_FLAG,
	DOUBLE_QUOTE_FLAG
}	t_quote

t_token	*register_n_token(const char *line, size_t n_token, size_t start, size_t end)
{
	t_token	*token;
	char	*word;

	token = NULL;
	word = ft_substr(line, start, end);
	if (word[0] != '\0')
	{
		token = init_token(n_token);
		token->word.word = word;
		printf("line      %s\n", line);
		printf("n_token   %zu\n", n_token);
		printf("start     %zu\n", start);
		printf("end       %zu\n", end);
		printf("substr    %s\n", word);
	}
	return (token);
}

size_t	last_index_of_current_token(const char *line, size_t start)
{
	size_t	end;

	end = start;
	while (!ft_isspace(line[end]) && line[end] != '\0')
		end++;
	return (end);
}

t_quote	set_flag_quote(char quote)
{
	if (SINGLE_QUOTE == quote)
		return (SINGLE_QUOTE_FLAG);
	else if (DOUBLE_QUOTE == quote)
		return (DOUBLE_QUOTE_FLAG);
	return (DEFAULT);
}

t_opereator_type	set_flag_operator(char *line, size_t i)
{
	char	or;
	char	and;

	or = '|';
	and = '&';
	if (line[i] == '\0')
		return (WORD)
	else if (line[i] == or && line[i + 1] == or)
		return (LOGICAL_OR);
	else if (line[i] == and && line[i + 1] == and)
		return (LOGICAL_AND)
	else if (line[i] == or)
		return (PIPE)
	return (WORD)
	
}

size_t	last_index(const char *line)
{
	size_t				i;
	t_quote				quote_flag;
	t_opereator_type	opereator_flag;
	t_redirect_type		redirect_flag;

	i = 0;
	quote_flag = DEFAULT;
	while (line[i] != '\0')
	{
		opereator_flag = set_flag_operator(line, i);
		redirect_flag = set_flag_redirect(line, i);
		if (quote_flag == DEFAULT && \
				(SINGLE_QUOTE == line[i] || DOUBLE_QUOTE == line[i]))
			quote_flag = set_flag_quote(line[i]);
		else if (quote_flag == set_flag_quote(line[i]))
			break ;
		else if (quote_flag == DEFAULT && line[i] == '|' || line[i] == '&')
			return ();
		else if (quote_flag == DEFAULT && line[i] == '>' || line[i] == '<')
		i++;
	}
	return (i);
}

t_token	*tokenize(const char *line)
{
	t_token	*token_head;
	t_token	*token;
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	n_token;

	i = 0;
	n_token = 0;
	start = i;
	end = last_index_of_current_token(line, start);
	token = register_n_token(line, n_token, start, end);
	token_head = token;
	while (line[i] != '\0')
	{
		i = end;
		while (ft_isspace(line[i]) && line[i] != '\0')
			i++;
		start = i;
		end = last_index_of_current_token(line, start);
		token->next = register_n_token(line, ++n_token, start, end);
		token = token->next;
	}
	return (token_head);
		//クウォートがある場合
		//クウォート判定(start)
		//判定したクウォート探索する関数(end)
		//文字列index(start~end)を作成する関数
		// if (line[i] == SINGLE_QUOTE || line[i] == DOUBLE_QUOTE)
		// {
		// 	while (line[i] != '\n' || line[i] == SINGLE_QUOTE || line[i] == DOUBLE_QUOTE)
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
}
