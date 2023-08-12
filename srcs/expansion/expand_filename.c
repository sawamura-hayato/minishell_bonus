/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:44:04 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/12 14:35:32 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include <stdio.h>
#include <dirent.h>

// 展開の流れ
// 1. 展開できるかどうかをチェックする
// 	- ワイルドカードかそれ以外か判定する関数
// 		- ワイルドカードの場合（flagを立ててワイルドカードかそれ以外か判定する関数へ）
// 		- それ以外の場合     （それ以外だったら文字列があるかどうか確認する）
// 			- flagがある場合 その文字が来るまでwhileで回す。次の文字が終端文字の場合はtrue判定,それ以外はfalse判定
// 			- flagがない場合 先頭ポインタをチェックする。ない場合はfalse判定
// 2. 展開する（1.でtrueの場合はtokenは分割する。理由はcdコマンドの時にパス名展開された先頭の文字列に対して実行されているから）

// 展開しない場合
// - そもそもワイルドカードがない場合をチェックする関数
// - ファイル名が展開できるかどうかをチェックする関数
// - クウォートがワイルドカードをカッコっている場合をチェックする関数
bool		expand_is_wildcard(char *word);
bool		expand_is_filename_word(char *word, char *target);
// t_filename	*new_filename(char *str);
// void		filename_addback(t_filename **head, t_filename *pDirent);

// 1.展開するかどうかチェックする関数
bool	expand_is_filename_word(char *word, char *target)
{
	bool	f_wildcard;

	f_wildcard = false;
	while (*word != '\0')
	{
		if(expand_is_wildcard(*word))
		{
			f_wildcard = true;
			word++;
		} 
		else
		{
			if (f_wildcard && *word == '\0')
				return (true);
			if (!f_wildcard && *word != *target)
				return (false);
			while (f_wildcard && *word != *target)
			{
				if (*taget == '\0')
					return (false);
				target++;
			}
			f_wildcard = false;
		}
	}
}

size_t	expand_filename_word_list_size(t_word_list *word_list)
{
	size_t	size;

	size = 0;
	while (word_list != NULL)
	{
		if (expand_is_filename_word())
			size++;
		word_list = word_list->next;
	}
	return (size);
}

void	expand_can_get_filename_word_list(t_word_list *word_list)
{
	struct dirent 	*pDirent;
	DIR				*pDir;
	char			*word_arr;
	size_t			size;
	size_t			i;

	size = expand_filename_word_list_size(word_list);
	if (size == 0)
		return ;
	word_arr = try_calloc(size, sizeof(char *));
	i = 0;
	try_opendir("./");
	while ((pDirent = try_readdir(pDir)) != NULL)
	{
		if (expand_is_filename_word(word_list->word, pDirent))
		{
			// 2.新しくfilenameの構造体を作成する関数
			if (word_list->filename == NULL)
				word_list->filename = new_filename(pDirent);
			else
				filename_addback(word_list->filename, new_filename(pDirent));
		}
		
	}
	closedir(pDir);
}

void	expand_filename_word_list(t_word_list *word_list)
{

	while (word_list != NULL)
	{
		if (expand_is_filename_word_list(word_list))
			expand_can_get_filename_word_list(word_list);
		word_list = word_list->next;
	}
	if (expand_is_filename_word_list(word_list))
}

void	expand_filename(t_ast *node)
{
	expand_filename_word_list(node->command_list->word_list);
	expand_filename_redirect_list(node->command_list->redirect_list);
}