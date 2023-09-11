/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:37:25 by tterao            #+#    #+#             */
/*   Updated: 2023/09/11 13:37:42 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include "builtins.h"
#include <signal.h>

/**
 * @brief この関数は、コマンドがbuiltinか判定する
 *
 * node->command_list->word_listがbuiltinか判定する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true builtinの場合、trueを返す
 * @return false builtinでない場合、falseを返す
 */
bool	exec_is_builtin(t_ast *node)
{
	char	*command;

	if (node->command_list->word_list == NULL
		|| node->command_list->word_list->word == NULL)
		return (false);
	command = node->command_list->word_list->word;
	return (
		ft_strcmp_ignorecase(command, "echo") == 0
		|| ft_strcmp_ignorecase(command, "cd") == 0
		|| ft_strcmp_ignorecase(command, "pwd") == 0
		|| ft_strcmp_ignorecase(command, "export") == 0
		|| ft_strcmp_ignorecase(command, "unset") == 0
		|| ft_strcmp_ignorecase(command, "env") == 0
		|| ft_strcmp_ignorecase(command, "exit") == 0
	);
}

static t_operator	get_left_operator(t_ast_node_type ast_type)
{
	if (PS_PIPE == ast_type)
		return (EXEC_PIPE);
	else if (PS_LOGICAL_AND == ast_type)
		return (EXEC_LOGICAL_AND);
	else if (PS_LOGICAL_OR == ast_type)
		return (EXEC_LOGICAL_OR);
	return (EXEC_START);
}

static t_operator	get_right_operator(t_operator operator)
{
	if (operator == EXEC_START)
		return (EXEC_END);
	else
		return (operator);
}

/**
 * @brief この関数はコマンドを実行する
 *
 * 第一引数の構文木nodeのタイプがコマンドの場合、node->command_listをコマンドとして、実行する
 * 第二引数のoperatorはコマンドの出力先を指定する。left_handにはnode->typeを渡し、
 * right_handには上のnodeから引き継いだoperatorを渡す
 * 一番初めのnode（初めにcommand_executionを呼ぶとき）は、operatorはEXEC_STARTになる
 * 一番最後に実行されるnodeのoperatorはEXEC_ENDになる
 * 第三引数のdは環境変数と終了ステータスを管理する
 *
 * @param node 構文木のnode
 * @param operator 構文木nodeの一つ上のnodeから引き継ぐoperator
 * @param d 環境変数と終了ステータス
 */
void	exec_command(t_ast *node, t_operator operator, t_data *d)
{
	bool	rd_success;

	if (node->left_hand != NULL)
		exec_command(node->left_hand, get_left_operator(node->type), d);
	if (node->right_hand != NULL)
		exec_command(node->right_hand, get_right_operator(operator), d);
	if (node->type == PS_COMMAND)
	{
		node->command_list->redirect_success = exec_do_redirection(node, d);
		rd_success = node->command_list->redirect_success;
		if (operator == EXEC_PIPE)
			exec_pipe(node, d);
		else if (!rd_success && operator == EXEC_START && exec_is_builtin(node))
			return ;
		else if (operator == EXEC_START || exec_is_builtin(node))
			return (builtin(node, NULL, true, d));
		else
			exec_fork(node, d);
	}
	if (operator == EXEC_START)
		exec_wait_child_process(node, d);
}
