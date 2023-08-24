/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:42:23 by tterao            #+#    #+#             */
/*   Updated: 2023/08/24 16:58:31 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "exec_command.h"
#include "library.h"
#define WRITE_BYTES 2000

static t_redirect_list	*exec_redirect_input(t_redirect_list *node, t_data *d)
{
	int		fd;
	char	*file;

	node = node->next;
	file = node->word;
	fd = try_open(open(file, O_RDONLY), file, d);
	if (fd == -1)
		return (NULL);
	try_dup2(fd, STDIN_FILENO, d);
	try_close(fd, d);
	return (node->next);
}

static t_redirect_list	*exec_redirect_output(t_command *command_list,
										t_redirect_list *r_node, t_data *d)
{
	int						fd;
	char					*file;
	const t_redirect_type	type = r_node->type;

	r_node = r_node->next;
	file = r_node->word;
	if (type == PS_REDIRECTING_OUTPUT)
		fd = try_open(open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644), file, d);
	else
		fd = try_open(open(file, O_CREAT | O_WRONLY | O_APPEND, 0644), file, d);
	if (fd == -1)
		return (NULL);
	command_list->fd = fd;
	return (r_node->next);
}

static t_redirect_list	*exec_redirect_heredoc(t_redirect_list *node, t_data *d)
{
	int		pipefd[2];
	size_t	i;
	ssize_t	write_bytes;

	// printf("%s", node->word);
	try_pipe(pipefd);
	try_write(pipefd[W], node->word, ft_strlen(node->word), d);
	// write_bytes = WRITE_BYTES + 1;
	// i = 0;
	// while (write_bytes > WRITE_BYTES)
	// {
	// 	write_bytes = write(pipefd[W],
	// 			&(node->word[i * WRITE_BYTES]), WRITE_BYTES);
	// 	if (write_bytes == -1)
	// 	{
	// 		perror("write");
	// 		d->exit_status = EXIT_FAILURE;
	// 		return (NULL);
	// 	}
	// 	i++;
	// }
	try_dup2(pipefd[R], STDIN_FILENO, d);
	try_close(pipefd[W], d);
	try_close(pipefd[R], d);
	return (node->next);
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
		if (r_node->type == PS_DELIMITER)
			r_node = exec_redirect_heredoc(r_node, d);
		else if (r_node->type == PS_REDIRECTING_OUTPUT
			|| r_node->type == PS_APPENDING_OUTPUT)
			r_node = exec_redirect_output(node->command_list, r_node, d);
		else if (r_node->type == PS_REDIRECTING_INPUT)
			r_node = exec_redirect_input(r_node, d);
	}
	return (true);
}
