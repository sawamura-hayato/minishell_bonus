/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:26 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/29 17:34:24 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_EXECUTION_H
# define COMMAND_EXECUTION_H

enum	e_operator
{
	HEAD,
	STDOUT,
	PIPE,
	LOGICAL_AND,
	LOGICAL_OR,
};

int		command_execution(t_ast *node, enum e_operator operator);
// int		do_input_redirection(t_redirect **input_redirect_list);
// int		do_output_redirection(t_redirect **output_redirect_list);
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
	else if (operator == HEAD && node->right_hand != NULL)
		command_execution(node->right_hand, STDOUT);
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
	if (operator == HEAD)
		wait_child_process(*node);
}

#endif