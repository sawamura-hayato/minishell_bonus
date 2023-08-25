/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:41:12 by tterao            #+#    #+#             */
/*   Updated: 2023/08/25 15:40:28 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"

/**
 * @brief この関数は、第一引数で与えられたnodeより下のnodeの子プロセスを待ち、終了ステータスを取得する。
 *
 * 第一引数で与えられたnode以下のコマンドをwaitpid()で待ち、終了ステータスを取得する。
 * &&, ||のnodeが出現した場合、そのnodeより左下のnodeは待たない。（既にそれらの子プロセスは終了しているため）
 *
 * @param node 構文木のnode
 */
void	exec_wait_child_process(t_ast *node, t_data *d)
{
	int	status;

	if (node->left_hand != NULL && node->type != PS_LOGICAL_AND
			&& node->type != PS_LOGICAL_OR)
		exec_wait_child_process(node->left_hand, d);
	if (node->right_hand != NULL)
		exec_wait_child_process(node->right_hand, d);
	if (node->type != PS_COMMAND)
		return ;
	if (node->command_list->pid == -1)
		status = EXIT_FAILURE;
	else
		waitpid(node->command_list->pid, &status, 0);
	d->exit_status = status;
}
