/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:48:29 by tterao            #+#    #+#             */
/*   Updated: 2023/08/28 14:22:58 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include "builtins.h"
#include <stdlib.h>

void	exec_is_error(const char *argv, const char *filepath, t_data *d);
void	exec_put_error_cmd_not_found(const char *command, t_data *d);
void	set_signal_exec(t_data *d);

static size_t	exec_get_argv_size(t_word_list *word_list)
{
	size_t		size;
	t_word_list	*node;

	size = 0;
	node = word_list;
	while (node != NULL)
	{
		if (node->word != NULL)
			size++;
		node = node->next;
	}
	return (size);
}

/**
 * @brief この関数はコマンド実行の二次元配列（argv）を作成する。
 *
 * node->command_list->word_listからコマンドを作成する。
 *
 * @param node 構文木のnode
 * @return char** コマンド実行の二次元配列（argv）
 */
char	**exec_make_argv(t_ast *node)
{
	char		**arr;
	t_word_list	*w_node;
	size_t		index;
	size_t		size;

	w_node = node->command_list->word_list;
	size = exec_get_argv_size(w_node);
	if (size == 0)
		return (NULL);
	arr = try_calloc(size + 1, sizeof(char *));
	index = 0;
	while (index < size)
	{
		if (w_node->word != NULL)
		{
			arr[index] = w_node->word;
			index++;
		}
		w_node = w_node->next;
	}
	return (arr);
}

static void	exec_pipefd(t_ast *node, int *pipefd, t_data *d)
{
	if (pipefd == NULL)
		return ;
	try_close(pipefd[R], d);
	if (node->command_list->fd == STDOUT_FILENO)
		try_dup2(pipefd[W], STDOUT_FILENO, d);
	try_close(pipefd[W], d);
}

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
void	exec_child_process(t_ast *node, int *pipefd, t_data *d)
{
	char	**argv;
	char	*filepath;

	if (node->command_list->word_list != NULL && exec_is_builtin(node))
		return (builtin(node, pipefd, false, d));
	// set_signal_exec(d);
	argv = exec_make_argv(node);
	filepath = exec_make_filepath(node, d);
	if (node->command_list->fd != STDOUT_FILENO)
	{
		try_dup2(node->command_list->fd, STDOUT_FILENO, d);
		try_close(node->command_list->fd, d);
	}
	exec_pipefd(node, pipefd, d);
	if (node->command_list->word_list == NULL)
		exit(EXIT_SUCCESS);
	exec_is_error(*argv, filepath, d);
	execve(filepath, (char *const *)argv, envs_make_envp(d->envs_hashmap));
	exec_put_error_cmd_not_found(*argv, d);
}
