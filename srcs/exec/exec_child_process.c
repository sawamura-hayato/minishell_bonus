/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:48:29 by tterao            #+#    #+#             */
/*   Updated: 2023/08/24 22:14:54 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include "builtins.h"
#include <stdlib.h>

static size_t	exec_get_argv_size(t_word_list *word_list)
{
	size_t		size;
	t_word_list	*node;

	size = 0;
	node = word_list;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}

// char	*exec_get_word_index(t_word_list **word_list)
// {
// 	char	*word;
// 	size_t	index;

// 	index = (*word_list)->index;
// 	word = try_strdup((*word_list)->word);
// 	(*word_list) = (*word_list)->next;
// 	while ((*word_list) != NULL && index == (*word_list)->index)
// 	{
// 		word = try_strjoin_free(word, (*word_list)->word);
// 		(*word_list) = (*word_list)->next;
// 	}
// 	return (word);
// }

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
		arr[index] = w_node->word;
		w_node = w_node->next;
		index++;
	}
	return (arr);
}

static void	exec_pipefd(t_ast *node, int *pipefd, t_data *d)
{
	if (pipefd == NULL)
		return ;
	if (node->command_list->fd == STDOUT_FILENO)
		try_dup2(pipefd[W], STDOUT_FILENO, d);
	try_close(pipefd[R], d);
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
#include <stdio.h>
void	exec_child_process(t_ast *node, int *pipefd, t_data *d)
{
	const char	**argv = (const char **)exec_make_argv(node);
	const char	*filepath = (const char *)exec_make_filepath(node, d);

	if (node->command_list->word_list != NULL && exec_is_builtin(node))
		return (builtin(node, pipefd, d));
	if (node->command_list->fd != STDOUT_FILENO)
	{
		try_dup2(node->command_list->fd, STDOUT_FILENO, d);
		try_close(node->command_list->fd, d);
	}
	exec_pipefd(node, pipefd, d);
	if (node->command_list->word_list == NULL)
		exit(EXIT_SUCCESS);

	// while (argv != NULL)
	// {
	// 	printf("%s\n", *argv);
	// 	argv++;
	// }
	exec_is_error(argv, filepath, d);
	execve(filepath, (char *const *)argv, envs_make_envp(d->envs_hashmap));
	exec_put_error_cmd_not_found(*argv, d);
}
