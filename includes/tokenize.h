/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/02 12:08:36 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

# include <stdbool.h>
# include <stddef.h>
 
typedef enum e_token_type {
	WORD,
	SINGL_QUOTE,
	DOBULE_QUOTE,
	LOGICAL_OR,
	LOGICAL_AND,
	PIPE,
}	t_token_type;

typedef enum e_quote {
	DEFAULT,
	SINGLE_QUOTE_FLAG,
	DOUBLE_QUOTE_FLAG
}	t_quote;

typedef struct s_token {
	char				*word;
	t_token_type		type;
	size_t				index;
	struct s_token		*next;
}	t_token;

// 入力　入力プロンプト（文字列）
// 出力　構造体token（単方向リスト）
// 役割　BNF記法の定義に従って入力値から単語に分割する。

// 定義
// word     : 単語（BNF記法の単語の定義）
// operator : 分割するために必要な特殊文字
// index  : トークンを識別するための番号
// 特殊文字　制御文字とリダイレクト文字

// 基本の流れ
// 入力プロンプトの先頭を見てクウォートかどうか判定する
// 構造体token作成(先頭ポインタが空白、タブ、改行、特殊文字の場合かつクウォートフラグがない場合によってindex発行)
// 入力プロンプトから分割したい文字列のサイズを出力する関数
// 3のサイズを使用して分割した文字列を出力する関数
// 分割した文字列を単方向リストに入れる関数
// 1,2,3,4を繰り返す（入力プロンプトの先頭ポインタは3で出力したサイズを加える）

t_token	*tokenize(const char *line);
bool	is_quote(char c);
bool	token_can_get_quote_token(t_token **token, const char **line, t_quote f_quote);
t_token	*init_token(size_t index);
t_token	*create_token(t_word word, t_operator_type operator, size_t index);
size_t	token_can_next_token_index(const char *line, t_quote f_quote, size index);
size_t	token_get_current_word_size(char *line, t_quote f_quote);
char	*token_get_current_word(char *line, size_t size);
t_token	*token_get_current_token(char **line, t_quote f_quote);
t_token	*token_addback(t_token **head, t_token *new_token);
t_token_type	get_token_type(char *word);


void	debug_print_token(t_token *token_list);

t_token	*token_get_current_token(char **line, t_quote f_quote)
{
	t_token	*current_token;
	size_t	index;
	size_t	size;
	char	*word;
	t_token_type	token;

	//構造体token作成(先頭ポインタが空白、タブ、改行、特殊文字の場合かつクウォートフラグがない場合によってindex発行)
	index = token_can_next_token_index(*line, f_quote, index);
	//入力プロンプトから分割したい文字列のサイズを出力する関数
	size = token_get_current_word_size(*line, f_quote);
	//3のサイズを使用して分割した文字列を出力する関数
	word = token_get_current_word(*line, size);
	token_type = get_token_type(word);
	current_token = create_token(word, token, index);
	prompt += size;
	return (current_token);
}

t_token	*tokenize(const char *line)
{
	t_token	*head;
	t_token	*token;
	t_quote	f_quote;

	f_quote = DEFAULT;
	while (*prompt != '\0')
	{
		if (token_can_get_quote_token(&head, &line, f_quote))
			continue ;
		token = token_get_current_token(&line, f_quote);
		token_addback(&head, token);
	}
	return (head);
}

#endif
