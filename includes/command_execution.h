/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:26 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/30 14:26:54 by tterao           ###   ########.fr       */
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

int		command_execution(t_ast *node, enum e_operator operator);
int		do_redirection(t_ast *node);
void	execute_fork(t_ast *node);
void	execute_pipe(t_ast *node);
int		execute_l_and(t_ast *node);
int		execute_l_or(t_ast *node);
void	child_process(t_ast *node, int *pipefd);
char	*get_filepath(t_ast *node);
char	**get_command_array(t_ast *node);
void	wait_child_process(t_ast *node);

int	command_execution(t_ast *node, enum	e_operator operator)
{
	if (node->left_hand != NULL)
		int ret = command_execution(node->left_hand, node->type);
	if (ret == )
		return ;
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		;
	else if (operator == START && node->right_hand != NULL)
		command_execution(node->right_hand, END);
	else if (node->right_hand != NULL)
		command_execution(node->right_hand, operator);
	if (node->type == COMMAND)
	{
		int rt = do_redirection(node);
		if (rt == )
		{
			//エラー処理
		}
		if (operator == PIPE)
			execute_pipe(node);
		else if (operator == LOGICAL_AND)
		{
			if (execute_l_and(node))
				command_execution(node->right_hand, operator);
		}
		else if (operator == LOGICAL_OR)
		{
			if (execute_l_or(node));
				command_execution(node->right_hand, operator);
		}
		else
			execute_fork(node);
	}
	if (operator == START)
		wait_child_process(*node);
}

#endif