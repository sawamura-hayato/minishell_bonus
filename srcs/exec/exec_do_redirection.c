/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:42:23 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 20:31:59 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "exec_command.h"
#include "library.h"

void			exec_put_error_ambiguous_redirect(char *file, t_data *d);
t_redirect_list	*exec_redirect_heredoc(t_redirect_list *node, t_data *d);

static t_redirect_list	*exec_redirect_input(t_redirect_list *node, t_data *d)
{
	int		fd;
	char	*file;

	node = node->next;
	file = node->word;
	if (node->is_ambiguous_error || file == NULL)
	{
		exec_put_error_ambiguous_redirect(file, d);
		return (NULL);
	}
	fd = try_open(open(file, O_RDONLY), file, d);
	if (fd == -1)
		return (NULL);
	try_dup2(fd, STDIN_FILENO, d);
	try_close(fd, d);
	return (node);
}

static t_redirect_list	*exec_redirect_output(t_command *command_list,
										t_redirect_list *r_node, t_data *d)
{
	int						fd;
	char					*file;
	const t_redirect_type	type = r_node->re_type;

	r_node = r_node->next;
	file = r_node->word;
	if (r_node->is_ambiguous_error || file == NULL)
	{
		exec_put_error_ambiguous_redirect(file, d);
		return (NULL);
	}
	if (type == PS_REDIRECTING_OUTPUT)
		fd = try_open(open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644), file, d);
	else
		fd = try_open(open(file, O_CREAT | O_WRONLY | O_APPEND, 0644), file, d);
	if (fd == -1)
		return (NULL);
	if (command_list->fd != STDOUT_FILENO)
		try_close(command_list->fd, d);
	command_list->fd = fd;
	return (r_node);
}

/**
 * @brief この関数はredirectionを実行する
 *
 * node->command_list->redirect_listを実行する
 * heredocの場合、heredocの文字列を標準入力に設定する
 * outputの場合、node->command_list->fdにopenしたfdを設定する
 * inputの場合、fileをopenし、readした文字列を標準入力に設定する
 *
 * @param operator
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true すべてのredirectionが問題なく成功した場合、trueを返す
 * @return false redirectionを失敗したタイミングで、この関数の処理を終了し、falseを返す
 *
 */
bool	exec_do_redirection(t_ast *node, t_data *d)
{
	t_redirect_list	*r_node;

	r_node = node->command_list->redirect_list;
	while (r_node != NULL)
	{
		if (r_node->re_type == PS_REDIRECTING_INPUT)
			r_node = exec_redirect_input(r_node, d);
		else if (r_node->re_type == PS_REDIRECTING_OUTPUT
			|| r_node->re_type == PS_APPENDING_OUTPUT)
			r_node = exec_redirect_output(node->command_list, r_node, d);
		else if (r_node->re_type == PS_DELIMITER
			|| r_node->re_type == PS_QUOTE_DELIMITER)
			r_node = exec_redirect_heredoc(r_node, d);
		if (r_node == NULL)
			return (false);
		r_node = r_node->next;
	}
	return (true);
}
