/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:01 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/11 15:23:39 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec_command.h"
#include <signal.h>

/**
 * @brief この関数はastの線形リストをそれぞれ実行する
 * @param node astの線形リストnode
 * @param d 環境変数と終了ステータス
 */
void	command_execution(t_ast_l1 *node, t_data *d)
{
	if (node->left_hand != NULL)
		command_execution(node->left_hand, d);
	if (node->type != AST_COMMAND && g_signal_num == SIGINT)
	{
		d->exit_status = SIGINT_EXITSTATUS;
		return ;
	}
	else if (
		(node->type == AST_LOGICAL_AND && d->exit_status == EXIT_SUCCESS)
		|| (node->type == AST_LOGICAL_OR && d->exit_status != EXIT_SUCCESS))
		command_execution(node->right_hand, d);
	if (node->type == AST_COMMAND)
	{
		try_dup2(d->dupped_stdinfd, STDIN_FILENO, d);
		exec_command(node->ast, EXEC_START, d);
	}
}
