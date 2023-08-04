/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/04 18:27:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdbool.h>
# include <stddef.h>
 
typedef enum e_token_type {
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
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
// token_type : 分割するために必要な特殊文字
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
bool	token_can_get_quote_token(t_token **token, char **line, \
									t_quote *f_quote, size_t index);
t_token	*init_token(size_t index);
t_token	*create_token(char *word, t_token_type token_type, size_t index);
t_quote	set_flag_quote(char quote);
t_token_type	set_flag_token(char *line, t_quote f_flag);
void	token_addback(t_token **head, t_token *new_token);
t_token_type	token_last_token_type(t_token *head);
size_t	token_get_current_word_size(char *line, t_quote f_quote);
size_t	token_can_next_token_index(t_token *head, char **line, t_quote f_quote, size_t index);
char	*token_get_current_word(char *line, size_t size);
void	token_get_current_token(t_token **head, char **line, t_quote f_quote, size_t *index);
bool	token_is_a_control_char(t_token_type token_type);

int		ft_isspace(char c);
bool	ft_is_special_char(char c);
size_t	ft_strlen(const char *str);

void	debug_print_token(t_token *token_list);

#endif
