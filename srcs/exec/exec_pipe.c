/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:59:46 by tterao            #+#    #+#             */
/*   Updated: 2023/09/01 15:17:46 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"

void	exec_close_fd(t_command *command, t_data *d);

void	exec_exit_if_redirect_failed(t_ast *node, int *pipefd, t_data *d)
{
	if (node->command_list->redirect_success)
		return ;
	if (pipefd != NULL)
	{
		try_close(pipefd[R], d);
		try_close(pipefd[W], d);
	}
	exit(d->exit_status);
}

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
void	exec_pipe(t_ast *node, t_data *d)
{
	pid_t	pid;
	int		pipefd[2];

	try_pipe(pipefd);
	pid = try_fork();
	if (pid == 0)
	{
		exec_exit_if_redirect_failed(node, pipefd, d);
		exec_child_process(node, pipefd, d);
	}
	else
	{
		node->command_list->pid = pid;
		exec_close_fd(node->command_list, d);
		try_dup2(pipefd[R], STDIN_FILENO, d);
		try_close(pipefd[W], d);
		try_close(pipefd[R], d);
	}
}
