/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/01 19:32:23 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdio.h>
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef enum e_word_type {
	DEFAULT,
	SINGL_QUOTE,
	DOBULE_QUOTE
}	t_word_type;

typedef enum e_opereator_type {
	WORD,
	LOGICAL_OR,
	LOGICAL_AND,
	PIPE,
}	t_operator_type;

typedef enum e_quote_type {
	DEFAULT,
	F_SINGL_QUOTE,
	F_DOUBLE_QUOTE,
}

typedef struct s_word {
	char		*word;
	t_word_type	type;
}	t_word;

typedef struct s_token {
	struct s_word		word;
	t_operator_type		operator;
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

t_token	*tokenize(const char *prompt);
bool	is_quote(char c);
bool	token_can_get_quote_token(t_token **token, const char *prompt, t_quote f_quote);
t_token	*init_token(size_t index);
t_token	*create_token(t_word word, t_operator_type operator, size_t index);
size_t	token_can_next_token_index(const char *prompt, t_quote f_quote, size index);
size_t	token_get_current_word_size(char *prompt, t_quote f_quote);
char	*token_get_current_word(char *prompt, size_t size);
t_token	*token_get_current_token(char **prompt, t_quote f_quote);
t_token	*token_addback(t_token **head, t_token *new_token);
t_operator_type	get_operator_type(char *word);


void	debug_print_token(t_token *token_list);

t_token	*token_get_current_token(char **prompt, t_quote f_quote)
{
	t_token	*current_token;
	size_t	index;
	size_t	size;
	char	*word;
	t_operator_type	operator;

	//構造体token作成(先頭ポインタが空白、タブ、改行、特殊文字の場合かつクウォートフラグがない場合によってindex発行)
	index = token_can_next_token_index(const char *prompt, t_quote f_quote, size index);
	//入力プロンプトから分割したい文字列のサイズを出力する関数
	size = token_get_current_word_size(char *prompt, t_quote f_quote);
	//3のサイズを使用して分割した文字列を出力する関数
	word = token_get_current_word(char *prompt, size_t word_size);
	operator = get_operator_type(word);
	current_token = create_token(word, operator, index);
	prompt += size;
	return (current_token);
}

t_token	*tokenize(const char *prompt)
{
	t_token	*head;
	t_token	*token;
	t_quote	f_quote;

	f_quote = DEFAULT;
	while (*prompt != '\0')
	{
		if (token_can_get_quote_token(head, prompt, f_quote))
			continue ;
		token = token_get_current_token(prompt, f_quote);
		token_addback(head, token);
	}
	return (head);
}

// t_tokne	*token_newtoken(t_token **head, const char *line, size_t start, size_t end);// substr使うなら、startとendのindexが必要
// void	token_set_token_type(t_token *token);
// void	token_addback(t_token **head, t_token *new_token);
// void	token_lasttoken(t_token **head);
// // void	token_remove_token(t_token **head, t_token *target);
// void	token_free_all_tokens(t_token **head);
// bool	token_is_meta_char(char c);// tokenの区切り文字
// bool	token_is_space(char c);//space＆tabは飛ばす 例）'     ls  | cat'
// bool	token_is_quotation(char c);

// t_token	*token_newtoken(const char *line, size_t start, size_t end)
// {
// 	t_token *newtoken;

// 	if (start == end && line[i] == '\0')
// 		return (NULL);
// 	newtoken = malloc_x(sizeof(t_token));
// 	newtoken->next = NULL;
// 	newtoken->word = substr_x(line, start, (end - start));
// 	token_set_token_type(newtoken);
// 	return (newtoken);
// }

// t_token	*tokenize(const char *line)
// {
// 	t_token *head;

// 	head = NULL;
// 	size_t	start = 0;
// 	size_t	i = 0;
// 	bool	quotation = false;
// 	char	target;
// 	while (line[i] != '\0')
// 	{
// 		while (token_is_space(line[i]) && line[i] != '\0')
// 			i++;
// 		i = start;
// 		while (!token_is_meta_char(line[i]) && quotation == false && line[i] != '\0')
// 		{
// 			if (token_is_quotation(line[i]) && line[i] == target)
// 			{
// 				if (!quotation)
// 					target = line[i];
// 				quotation = !quotation;
// 			}
// 			i++;
// 		}
// 		t_token *token =  token_newtoken(line, start, i)
// 		token_addback(head, token);
// 	}
// 	return (head);
// }

#endif
