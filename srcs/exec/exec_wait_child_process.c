/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:41:12 by tterao            #+#    #+#             */
/*   Updated: 2023/08/24 21:19:09 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"

/**
 * @brief この関数は、第一引数で与えられたnodeより下のnodeの子プロセスを待ち、終了ステータスを取得する。
 *
 * 第一引数で与えられたnode以下のコマンドをwaitpid()で待ち、終了ステータスを取得する。
 * &&, ||のnodeが出現した場合、そのnodeとそのnodeより下のnodeは待たない。（既にそれらのプロセスは終了しているため）
 *
 * @param node 構文木のnode
 */
void	exec_wait_child_process(t_ast *node, t_data *d)
{
	int	status;

	if (node->left_hand != NULL)
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
