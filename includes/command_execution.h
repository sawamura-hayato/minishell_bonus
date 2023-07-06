/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:26 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/06 20:03:34 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_EXECUTION_H
# define COMMAND_EXECUTION_H

enum	e_operator
{
	START,
	END,
	PIPE,
	LOGICAL_AND,
	LOGICAL_OR,
};

int		command_execution(t_ast *node, enum e_operator operator, t_envs **envs);
int		do_redirection(t_ast *node);
void	execute_fork(t_ast *node);
void	execute_pipe(t_ast *node);
int		execute_l_and(t_ast *node);
int		execute_l_or(t_ast *node);
void	child_process(t_ast *node, int *pipefd);
char	*make_filepath(t_ast *node);
char	**make_command_array(t_ast *node);
void	wait_child_process(t_ast *node);
bool	is_builtin(t_ast *node);

int	command_execution(t_ast *node, enum	e_operator operator, t_envs **envs)
{
	if (node->left_hand != NULL)
		command_execution(node->left_hand, node->type, envs);
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		;
	else if (node->right_hand != NULL)
		command_execution(node->right_hand, operator, envs);
	else if (operator == START && node->right_hand != NULL)
		command_execution(node->right_hand, END, envs);
	if (node->type == COMMAND)
	{
		int rt = do_redirection(node);
		if (rt == )
		{
			//エラー処理
			//redirectionが失敗したらこのノードのコマンドを実行しない
			//open readが失敗したときなど
			return;
		}
		if (operator == PIPE)
			execute_pipe(node);
		else if (operator == LOGICAL_AND)
		{
			if (execute_l_and(node))
				command_execution(node->right_hand, operator, envs);
		}
		else if (operator == LOGICAL_OR)
		{
			if (execute_l_or(node));
				command_execution(node->right_hand, operator, envs);
		}
		else if (operator == START && is_builtin(node))//operatorなしかつ実行するのはbuiltinのみなので、親プロセスで実行
			return (do_builtin(node, envs));
		else
			execute_fork(node);
	}
	if (operator == START)
		wait_child_process(node);
}

#endif