/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:46:09 by tterao            #+#    #+#             */
/*   Updated: 2023/08/26 13:50:04 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"

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

	// dprintf(STDERR_FILENO, "fork\n");
	pid = try_fork();
	if (pid == 0)
		exec_child_process(node, NULL, d);
	else
		node->command_list->pid = pid;
}
