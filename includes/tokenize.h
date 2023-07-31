/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/31 18:23:40 by hsawamur         ###   ########.fr       */
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

typedef struct s_word {
	char		*word;
	t_word_type	type;
}	t_word;

typedef struct s_token {
	struct s_word		word;
	t_operator_type		operator;
	size_t				n_token;
	struct s_token		*next;
}	t_token;


// 入力　入力プロンプト（文字列）
// 出力　構造体token（単方向リスト）
// 役割　BNF記法の定義に従って入力値から単語に分割する。

// 定義
// word     : 単語（BNF記法の単語の定義）
// operator : 分割するために必要な特殊文字
// n_token  : トークンを識別するための番号
// 特殊文字　制御文字とリダイレクト文字

// 基本の流れ
// 1. 構造体token作成(先頭ポインタが空白、タブ、改行、特殊文字の場合かつクウォートフラグがない場合によってindex発行)
// 2. 入力プロンプトから分割したい文字列のサイズを出力する関数
// 3. 分割した文字列を出力する関数
// 4. 分割した文字列を単方向リストに入れる関数
// 5. 1,2,3,4を繰り返す（入力プロンプトの先頭ポインタは1で出力したサイズを加える）

// 1の流れ（char *new_prompt, t_quote f_quote）
// 入力プロンプトの文字列を一つずつ判定する。以下はどのような場合にのみ単語のサイズが出力されるのかを記述する
// クウォートのフラグがある場合　空白、タブ、改行、特殊文字などはただの文字列になる。
// - 終端文字→エラー判定（* parseで行うかどうかは議論が必要）
// - 同じタイプのクウォートを発見した場合、出力
// クウォートのフラグがない場合
// - 特殊文字
// - 空白文字、改行など
// - 終端文字

//* parseで行うかどうかは議論が必要
//特殊文字が連続で来た場合と同じときにエラー処理をするのか。その場合は全体をフリーかつexit_status、またhistoryも必要になってくる。

// main（4）で入力プロンプトの先頭を見てf_quoteかどうか判定する。
// - 
// "kk"dd 'ee'
// " -> kk -> " -> dd  -> ' -> ee -> '
// クウォートフラグはenumで定義し、判定する。（シングルかダブルかを判定するため）

t_word	init_word(void);
t_word	create_word(char *new_word, t_word_type type);
t_token	*init_token(size_t n_token);
t_token	*create_token(t_word word, t_operator_type operator, size_t n_token);
void	debug_print_token(t_token *token_list);
t_token	*tokenize(const char *line);
// t_token	*tokenize(const char *line);
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
