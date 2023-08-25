/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:59:46 by tterao            #+#    #+#             */
/*   Updated: 2023/08/26 01:11:48 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"

/**
 * @brief この関数はforkを実行し、子プロセスを生成する。親プロセスは子プロセスの実行結果を受け取る。
 *
 * pipe関数を使用して、プロセス間通信を行うための、fdを二つ用意する。
 * pipefdを通じて、子プロセスの実行結果を親プロセスの標準入力に設定する。
 * 親プロセスで、pipefdをcloseする。
 * 子プロセスのidをnode->command_list->pidに代入する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 */
#include <stdio.h>
void	exec_pipe(t_ast *node, t_data *d)
{
	pid_t	pid;
	int		pipefd[2];

	// dprintf(STDERR_FILENO, "pipe\n");
	pid = try_fork();
	try_pipe(pipefd);
	if (pid == 0)
		exec_child_process(node, pipefd, d);
	else
	{
		node->command_list->pid = pid;
		try_close(pipefd[W], d);
		try_dup2(pipefd[R], STDIN_FILENO, d);
		try_close(pipefd[R], d);
	}
}
