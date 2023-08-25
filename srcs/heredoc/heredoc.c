/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:47:46 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/25 19:11:15 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

bool	heredoc_get_str(t_redirect_list *node, t_data *d)
{
	t_redirect_list	*delimiter;

	delimiter = node->next;
	if (delimiter == NULL)
		return (false);
	/* if (delimiter->type == PS_QUOTE_DELIMITER) */
	/* heredoc_delete_quote(delimiter); */
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
				return (false);
			tmp = node->next;
			redirect_delete(command, node);
			node = tmp;
		}
		else
			node = node->next;
	}
	return (true);
}

bool	heredoc(t_ast *node, t_data *d)
{
	bool	result;

	result = true;
	if (node->left_hand != NULL)
		result = heredoc(node->left_hand, d);
	if (result && node->right_hand != NULL)
		result = heredoc(node->right_hand, d);
	if (result == false)
		return (false);
	if (node->type == PS_COMMAND)
		return (heredoc_redirect_list(node->command_list, d));
	return (true);
}
