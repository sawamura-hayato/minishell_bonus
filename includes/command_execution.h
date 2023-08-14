/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:26 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/08 20:48:49 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_EXECUTION_H
# define COMMAND_EXECUTION_H

typedef enum e_operator
{
	START,
	END,
	PIPE,
	LOGICAL_AND,
	LOGICAL_OR,
}	t_operator;

enum e_pipefd
{
	R = 0,//read用fd
	W = 1,//write用fd
};

/**
 * @brief この関数はコマンドを実行する
 *
 * 第一引数の構文木nodeのタイプがコマンドの場合、node->command_listをコマンドとして、実行する
 * 第二引数のoperatorはコマンドの出力先を指定する。left_handにはnode->typeを渡し、right_handには上のnodeから引き継いだoperatorを渡す
 * 一番初めのnode（初めにcommand_executionを呼ぶとき）は、operatorはSTARTになる
 * 一番最後に実行されるnodeのoperatorはENDになる
 * 第三引数のdは環境変数と終了ステータスを管理する
 *
 * @param node 構文木のnode
 * @param operator 構文木nodeの一つ上のnodeから引き継ぐoperator
 * @param d 環境変数と終了ステータス
 */
void	command_execution(t_ast *node, enum e_operator operator, t_data *d);

/**
 * @brief この関数はredirectionを実行する
 *
 * node->command_list->redirect_listを実行する
 * heredocの場合、heredocの文字列を標準入力に設定する
 * outputの場合、node->command_list->fdにopenしたfdとfd_typeを設定する
 * inputの場合、fileをopenし、readした文字列を標準入力に設定する
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true すべてのredirectionが問題なく成功した場合、trueを返す
 * @return false redirectionを失敗したタイミングで、この関数の処理を終了し、falseを返す
 */
bool	exec_do_redirection(t_ast *node, t_data *d);

/**
 * @brief この関数はforkを実行し、子プロセスを生成する。
 *
 * 子プロセスのidをnode->command_list->pidに代入する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 */
void	exec_fork(t_ast *node, t_data *d);

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
void	exec_pipe(t_ast *node, t_data *d);

/**
 * @brief この関数はforkを実行し、子プロセスを生成する。
 *
 * exec_fork()を実行する。
 * exec_wait_child_process()で終了ステータスを取得する。
 * 終了ステータスが0（正常終了）の場合、trueを返す。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true コマンドを実行した結果、終了ステータスが0の場合、trueを返す
 * @return false コマンドを実行した結果、終了ステータスが0以外の場合、falseを返す
 */
bool	exec_l_and(t_ast *node, t_data *d);

/**
 * @brief この関数はforkを実行し、子プロセスを生成する。
 *
 * exec_fork()を実行する。
 * exec_wait_child_process()で終了ステータスを取得する。
 * 終了ステータスが0（正常終了）以外の場合、trueを返す。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true コマンドを実行した結果、終了ステータスが0以外の場合、trueを返す
 * @return false コマンドを実行した結果、終了ステータスが0の場合、falseを返す
 */
bool	exec_l_or(t_ast *node, t_data *d);

/**
 * @brief この関数は子プロセス内でコマンドを実行する。
 *
 * node->command_list->fdに、コマンドを出力する。
 * pipefdがNULL出ないとき、かつfd_typeがSTDOUTの場合、pipefd[W]にコマンドを出力する。
 *
 * @param node 構文木のnode
 * @param pipefd pipeがない場合は、NULLが与えられる
 * @param d 環境変数と終了ステータス
 */
void	exec_child_process(t_ast *node, int *pipefd, t_data *d);

/**
 * 	@brief この関数は、commandのpathを取得する。
 *
 * commandの絶対pathを取得する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return char* commandのpath
 */
char	*exec_make_filepath(t_ast *node, t_data *d);

/**
 * @brief この関数はコマンド実行の二次元配列（argv）を作成する。
 *
 * node->command_list->word_listからコマンドを作成する。
 *
 * @param node 構文木のnode
 * @return char** コマンド実行の二次元配列（argv）
 */
char	**exec_make_command_array(t_ast *node);

/**
 * @brief この関数は、第一引数で与えられたnodeより下のnodeの子プロセスを待ち、終了ステータスを取得する。
 *
 * 第一引数で与えられたnode以下のコマンドをwaitpid()で待ち、終了ステータスを取得する。
 * &&, ||のnodeが出現した場合、そのnodeとそのnodeより下のnodeは待たない。（既にそれらのプロセスは終了しているため）
 *
 * @param node 構文木のnode
 */
void	exec_wait_child_process(t_ast *node, t_data *d);

/**
 * @brief この関数は、コマンドがbuiltinか判定する
 *
 * node->command_list->word_listがbuiltinか判定する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true builtinの場合、trueを返す
 * @return false builtinde出ない場合、falseを返す
 */
bool	exec_is_builtin(t_ast *node);

void	command_execution(t_ast *node, enum	e_operator operator, t_data *d)
{
	if (node->left_hand != NULL)
		command_execution(node->left_hand, node->type, &d);
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		;
	else if (node->right_hand != NULL)
		command_execution(node->right_hand, operator, &d);
	else if (operator == START && node->right_hand != NULL)
		command_execution(node->right_hand, END, &d);
	if (node->type == COMMAND)
	{
		bool	ret = do_redirection(node, &d);
		if (ret == false && operator != LOGICAL_OR)
		{
			//エラー処理
			//redirectionが失敗したらこのノードのコマンドを実行しない
			//open readが失敗したときなど
			return;
		}
		else if (ret == false && operator == LOGICAL_OR)//operator=LOGICAL_ORの場合、次のコマンドを実行
		{
			exec_wait_child_process(node);
			command_execution(node->right_hand, operator, &d);
		}
		else if (operator == PIPE)
			exec_pipe(node);
		else if (operator == LOGICAL_AND)
		{
			if (exec_l_and(node))
				command_execution(node->right_hand, operator, &d);
		}
		else if (operator == LOGICAL_OR)
		{
			if (exec_l_or(node));
				command_execution(node->right_hand, operator, &d);
		}
		else if (operator == START && exec_is_builtin(node))//operatorなしかつ実行するのはbuiltinのみなので、親プロセスで実行
			return (builtin(node, NULL, &d));//builtin.hの関数
		else
			exec_fork(node, &d);
	}
	if (operator == START)
		exec_wait_child_process(node, &d);
}

#endif