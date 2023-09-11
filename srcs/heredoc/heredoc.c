/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:47:46 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/11 16:14:11 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <readline/readline.h>
#include <readline/history.h>

void	get_signal_num(t_data *d);
void	set_signal_heredoc(t_data *d);
void	ignore_signal(t_data *d);
void	expand_delete_quotation_redirect(t_redirect_list *redirect);

bool	heredoc_get_str(t_redirect_list *node, t_data *d)
{
	t_redirect_list	*delimiter;

	delimiter = node->next;
	if (delimiter == NULL)
		return (false);
	if (delimiter->re_type == PS_QUOTE_DELIMITER)
		expand_delete_quotation_redirect(delimiter);
	set_signal_heredoc(d);
	try_dup2(d->dupped_stdinfd, STDIN_FILENO, d);
	return (heredoc_read_loop(delimiter, d));
}

bool	heredoc_redirect_list(t_command *command, t_data *d)
{
	t_redirect_list	*node;
	t_redirect_list	*tmp;

	node = command->redirect_list;
	while (node != NULL)
	{
		if (node->re_type == PS_HERE_DOCUMENTS)
		{
			if (heredoc_get_str(node, d) == false)
			{
				ignore_signal(d);
				return (false);
			}
			ignore_signal(d);
			tmp = node->next;
			redirect_delete(command, node);
			node = tmp;
		}
		else
			node = node->next;
	}
	return (true);
}

static void	heredoc_signal_newline(t_data *d)
{
	get_signal_num(d);
	try_write(STDERR_FILENO, "\n", 1, d);
}

bool	heredoc_l2(t_ast *node, t_data *d)
{
	bool	result;

	result = true;
	if (node->left_hand != NULL)
		result = heredoc_l2(node->left_hand, d);
	if (result && node->right_hand != NULL)
		result = heredoc_l2(node->right_hand, d);
	if (result == false)
		return (false);
	if (node->type == PS_COMMAND)
		result = heredoc_redirect_list(node->command_list, d);
	if (result == false)
		heredoc_signal_newline(d);
	return (result);
}

bool	heredoc(t_ast_l1 *node, t_data *d)
{
	bool	result;

	result = true;
	if (node->left_hand != NULL)
		result = heredoc(node->left_hand, d);
	if (result && node->right_hand != NULL)
		result = heredoc(node->right_hand, d);
	if (result == false)
		return (false);
	if (node->type == AST_COMMAND)
		result = heredoc_l2(node->ast, d);
	return (result);
}
