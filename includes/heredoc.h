/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:26:57 by tterao            #+#    #+#             */
/*   Updated: 2023/08/22 13:13:51 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "parse.h"
# include "init.h"
# include "library.h"

# include <stdbool.h>

/**
 * @brief この関数は、heredocを実行する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true すべてheredocに成功した場合（heredocがない場合も含む）、trueを返す
 * @return false heredocに失敗もしくはシグナルを受け取りheredocを終了した場合、falseを返す
 */
bool	heredoc(t_ast *node, t_data *d);

/**
 * @brief この関数は、線形リストのredirect_listのnodeを一つずつheredocか確認する。
 *
 * nodeがheredocの場合、heredocを実行する。
 * heredocが失敗した場合、falseを返す。
 *
 * @param command commandのnode
 * @param d 環境変数と終了ステータス
 * @return true heredocを実行し、文字列を取得できた場合、trueを返す
 * @return false heredocを実行し、文字列を取得できなかった場合、falseを返す
 */
bool	heredoc_redirect_list(t_command *command, t_data *d);

/**
 * @brief この関数は、heredocを実行し、文字列を取得する。
 *
 * @param node heredocのnode
 * @param d 環境変数と終了ステータス
 * @return true
 * @return false
 */
bool	heredoc_get_str(t_redirect_list *node, t_data *d);

/**
 * @brief この関数は、delimiterのクォートを削除する。
 *
 * @param delimiter delimiterのnode
 */
void	heredoc_delete_quote(t_redirect_list *delimiter);

/**
 * @brief この関数は、targetのnodeを線形リストcommand->redirect_listから削除する。
 *
 *
 * @param command redirect_listを保持しているcommandのnode
 * @param target 削除するnode
 */
void	redirect_delete(t_command *command, t_redirect_list *target);

/**
 * @brief この関数は、delimiterが標準入力から取得されるまで、loopする。
 *
 * @param delimiter delimiterのnode
 * @return true 標準入力がdelimiterが取得された場合、trueを返す
 * @return false 標準入力からdelimiterの取得を失敗もしくはシグナルを取得した場合、falseを返す
 */
bool	heredoc_read_loop(t_redirect_list *delimiter);

/**
 * @brief この関数は、標準入力から文字列を取得する。
 *
 * @return char* 改行まで入力された文字列もしくはNULLを返す。
 */
char	*heredoc_read();


bool	heredoc_read_loop(t_redirect_list *delimiter)
{
	char	*str = try_strdup("");

	while (true)
	{
		char *buff = heredoc_read();
		if (buff == NULL)
		{
			free(str);
			return (false);
		}
		if (ft_strcmp(buff, delimiter->word) == 0)
		{
			free(buff);
			delimiter->word = str;
			break ;
		}
		tmp = str;
		str = try_strjoin(str, buff);
		free(buff);
		free(tmp);
	}
	return (true);
}

bool	heredoc_get_str(t_redirect_list *node, t_data *d)
{
	t_redirect_list	*delimiter = node->next;
	char		*tmp;

	if (delimiter == NULL)
		return (false);
	if (delimiter->type == QUOTE_DELIMITER)
		heredoc_delete_quote(delimiter);
	return (heredoc_read_loop(delimiter));
}

bool	heredoc_redirect_list(t_command *command, t_data *d)
{
	t_redirect_list	*node = command->redirect_list;

	while (node != NULL)
	{
		if (node->type == HERE_DOCUMENTS)
		{
			if (heredoc_get_str(node, d) == false)
				return (false);
			redirect_delete(command, node);
		}
		node = node->next;
	}
	return (true);
}


bool	heredoc(t_ast *node, t_data *d)
{
	bool	result;

	if (node->left_hand != NULL)
		result = heredoc(node->left_hand, d);
	if (result && node->right_hand != NULL)
		result = heredoc(node->right_hand, d);
	if (result == false)
		return (false);
	if (node->type == COMMAND)
		return (heredoc_redirect_list(node->command_list, d));
	return (true);
}

#endif
