/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:26 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/28 13:56:46 by tterao           ###   ########.fr       */
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

void	command_execution(t_ast *node, enum e_operator operator);
// int		do_input_redirection(t_redirect **input_redirect_list);
// int		do_output_redirection(t_redirect **output_redirect_list);
int		do_redirection(t_ast *node);
void	execute_fork(t_ast *node, enum e_operator operator);
void	child_process(t_ast *node, int *pipefd);
char	*get_filepath(t_ast *node);
char	**get_command_array(t_ast *node);
void	wait_child_process(t_ast *node);

void	command_execution(t_ast *node, enum	e_operator operator)
{
	if (node->left_hand != NULL)
		command_execution(node->left_hand, node->type);
	else if (operator == HEAD && node->right_hand != NULL)
		command_execution(node->right_hand, node->type);
	else if (node->right_hand != NULL)
		command_execution(node->right_hand, operator);
	if (node->type == COMMAND)
	{
		// int rt = do_input_redirection(node->input_redirect_list)
		// if (rt == )
		// {
		// 	//エラー処理
		// }
		// int fd = do_output_redirection(node->output_redirect_list);
		int rt = do_redirection(node);
		if (rt)
		{
			//エラー処理
		}
		if (operator == PIPE)
			execute_pipe(node);
		else if (operator == LOGICAL_AND)
			execute_l_and(node)
		else if (operator == LOGICAL_OR)
			execute_l_or(node);
		else
			execute_fork(node);
	}
	if (operator == HEAD)
		wait_child_process(t_ast *node);
}

#endif