/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:46:09 by tterao            #+#    #+#             */
/*   Updated: 2023/09/02 17:33:11 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"

void	exec_close_fd(t_command *command, t_data *d);
void	exec_exit_if_redirect_failed(t_ast *node, int *pipefd, t_data *d);

/**
 * @brief この関数はforkを実行し、子プロセスを生成する。
 *
 * 子プロセスのidをnode->command_list->pidに代入する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 */
void	exec_fork(t_ast *node, t_data *d)
{
	pid_t	pid;

	pid = try_fork();
	if (pid == 0)
	{
		exec_exit_if_redirect_failed(node, NULL, d);
		exec_child_process(node, NULL, d);
	}
	else
	{
		node->command_list->pid = pid;
		exec_close_fd(node->command_list, d);
		try_close(STDIN_FILENO, d);
	}
}
