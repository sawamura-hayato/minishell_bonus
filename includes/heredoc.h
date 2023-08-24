/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:26:57 by tterao            #+#    #+#             */
/*   Updated: 2023/08/23 20:41:07 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# define BUFFER_SIZE 1024
# include "init.h"
# include "library.h"
# include "parse.h"
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
bool	heredoc_read_loop(t_redirect_list *delimiter, t_data *d);

/**
 * @brief この関数は、標準入力から文字列を取得する。
 *
 * @return char* 改行まで入力された文字列もしくはNULLを返す。
 */
char	*heredoc_read(t_data *d);

/* bool	heredoc_read_loop(t_redirect_list *delimiter); */

bool	heredoc_get_str(t_redirect_list *node, t_data *d);

bool	heredoc_redirect_list(t_command *command, t_data *d);

bool	heredoc(t_ast *node, t_data *d);

#endif
