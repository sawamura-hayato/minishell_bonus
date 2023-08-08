/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:23 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/08 16:25:56 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "parse.h"
#include "init.h"
#include <stdlib.h>

//expansion.c
int			expansion(t_ast *node, const t_data **d);

//expand_variable.c
void	expand_variable(t_ast *node, const t_data *d);
char	*expand_convert_doller_word(char **word, t_data *d);
char	*expand_get_expanded_token_word(char *token_word, t_data *d);
void	expand_token_word_list(t_word_list *token, t_data *d);
void	expand_token_redirect_list(t_redirect *token, t_data *d);
void	expand_variable_word_list(t_word_list *head, t_data *d);
void	expand_variable_redirect_list(t_redirect *head, t_data *d);

//
void		expand_word_splitting(t_ast *node);//IFSを確認 クオテーションで囲まれていない && スペースがある場合、線形リストのトークンを分割
void		expand_filename(t_ast *node);//＊の展開 + 線形リストのトークンを追加
void		expand_quotation(t_ast *node);//クオテーションの削除
char		*get_env_x(char *target, const t_data **d);
t_command	*command_split_node(t_command *node);//word splittingでノードを分割
t_redirect	*redirect_add_node(t_redirect *node);//word splittingでノードを分割

//heredoc
void		do_heredoc(t_ast *node);//heredocを実行し、文字列を取得
void		expand_heredoc(t_ast *node, const t_data **d);//delimiterにクオテーションがない場合、環境変数を展開


t_command	*command_split_node(t_command *node)
{

	t_command	*next = node->next;
	//一番最初はnode->wordだけ変更する
	if (is_ifs(node->word, try_get_env("IFS", d)))
	{
		//[testa   b   c+test] -> [testa] [b   c+test]
		char	*tmp = node->word;
		node->word = try_substr(node->word, 0, strchr(node->word, try_get_env("IFS", d)) - node->word[0]);
		t_command	*newnode = try_strdup(strchr(node->word, try_get_env("IFS", d)));
		free(tmp);
	}
	//ifs区切り文字がある限りloop
	//[testa] [b   c  test] -> [b] [c+test]
	//final result = [a] [b] [c+test]
	while (is_ifs(node->word, try_get_env("IFS", d)))
	{
		//ifs区切り文字がwordにあった場合、その文字アドレスを取得
		//command_newnodeの中で、strchrの返り値のアドレスをstrdupする
		t_command	*tmp = node;
		newnode = command_newnode(strchr(is_ifs(node->word, try_get_env("IFS", d))));
		tmp->next = newnode;
	}
	newnode->next = next;
}

#endif
