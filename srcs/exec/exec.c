/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:01 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/24 14:43:23 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "exec_command.h"
#include "parse.h"
// #include "expansion.h"
#define WRITE_BYTES 2000

size_t	exec_get_size_arr_word_list(t_word_list *word_list)
{
	size_t	size;
	size_t	index;

	size = 1;
	// if (word_list == NULL)
	// 	return (0);
	index = word_list->index;
	while (true)
	{
		word_list = word_list->next;
		if (word_list == NULL)
			break ;
		if (index != word_list->index)
		{
			index = word_list->index;
			size++;
		}
	}
	return (size);
}

// size_t	command_get_size_word_index(t_word_list **word_list, size_t index)
// {

// }

char	*exec_get_word_index(t_word_list **word_list)
{
	char	*word;
	size_t	index;

	index = (*word_list)->index;
	word = try_strdup((*word_list)->word);
	(*word_list) = (*word_list)->next;
	while ((*word_list) != NULL && index == (*word_list)->index)
	{
		word = try_strjoin_free(word, (*word_list)->word);
		(*word_list) = (*word_list)->next;
	}
	return (word);
}

char	**exec_change_word_list_to_double_arr(t_word_list *word_list)
{
	char	**arr;
	size_t	index;
	size_t	size;

	size = exec_get_size_arr_word_list(word_list);
	if (size == 0)
		return (NULL);
	arr = try_malloc((size + 1) * sizeof(char *));
	arr[size] = NULL;
	index = 0;
	while (index < size)
	{
		arr[index] = exec_get_word_index(&word_list);
		index++;
	}
	return (arr);
}

t_operator	exec_change_ast_type_to_operator(t_ast_node_type ast_type)
{
	if (PS_PIPE == ast_type)
		return (EXEC_PIPE);
	else if (PS_LOGICAL_AND == ast_type)
		return (EXEC_LOGICAL_AND);
	else if (PS_LOGICAL_OR == ast_type)
		return (EXEC_LOGICAL_OR);
	return (EXEC_START);
}

void	exec_search_command(t_ast *node, t_operator operator, t_data *d)
{

	if (node->left_hand != NULL)
		exec_command(node->left_hand, exec_change_ast_type_to_operator(node->type), d);
	if (node->type == PS_LOGICAL_AND || node->type == PS_LOGICAL_OR)
		;
	else if (node->right_hand != NULL)
		exec_command(node->right_hand, operator, d);
	else if (operator== EXEC_START && node->right_hand != NULL)
		exec_command(node->right_hand, EXEC_END, d);
}

/**
 * @brief この関数はredirectionを実行する
 *
 * node->command_list->redirect_listを実行する
 * heredocの場合、heredocの文字列を標準入力に設定する
 * outputの場合、node->command_list->fdにopenしたfdとfd_typeを設定する
 * inputの場合、fileをopenし、readした文字列を標準入力に設定する
 *
 * @param operator
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true すべてのredirectionが問題なく成功した場合、trueを返す
 * @return false redirectionを失敗したタイミングで、この関数の処理を終了し、falseを返す
 * //どういうタイミングで失敗するのか？
 *
 */
// bool exec_do_redirection(t_ast *node, t_data *d);

t_redirect_list	*exec_redirect_input(t_redirect_list *node, t_data *d)
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

t_redirect_list	*exec_redirect_output(t_command *command_list, t_redirect_list *r_node, t_data *d)
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

t_redirect_list	*exec_redirect_heredoc(t_redirect_list *node, t_data *d)
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

void	exec_do_redirection(t_ast *node, t_data *d)
{
	t_redirect_list	*r_node;

	r_node = node->command_list->redirect_list;
	// printf("%p\n", r_node);
	while (r_node != NULL)
	{
		if (r_node->type == PS_DELIMITER)
		{
		// heredocの場合、heredocの文字列を標準入力に設定する
		//色々やり方がある（fd, readとwrite）
			r_node = exec_redirect_heredoc(r_node, d);
		}
		else if (r_node->type == PS_REDIRECTING_OUTPUT || r_node->type == PS_APPENDING_OUTPUT)
		{
		// outputの場合、r_node->command_list->fdにopenしたfdとfd_typeを設定する
			r_node = exec_redirect_output(node->command_list, r_node, d);
		}
		else if (r_node->type == PS_REDIRECTING_INPUT)
		{
		// inputの場合、fileをopenし、readした文字列を標準入力に設定する
			r_node = exec_redirect_input(r_node, d);
		}
	}
}

/**
 * @brief この関数はforkを実行し、子プロセスを生成する。
 *
 * 子プロセスのidをnode->command_list->pidに代入する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 */
// void exec_fork(t_ast *node, t_data *d);

void	exec_child_process(t_ast *node, int *pipefd, t_data *d)
{
	char	**argv;
	char	*filepath;
	int	fd;

	(void)pipefd;
	fd = node->command_list->fd;
	if (fd != STDOUT_FILENO)
	{
		try_dup2(fd, STDOUT_FILENO, 0);
		try_close(fd, d);
	}
	if (node->command_list->word_list != NULL)
	{
		argv = exec_change_word_list_to_double_arr(node->command_list->word_list);
		filepath = exec_make_filepath(node, d);
		char **tmp = argv;
		// while (*tmp)
		// {
			// printf("argv=%s\n", *tmp);
		// 	tmp++;
		// }
		// printf("path=%s\n", filepath);
		execve(filepath, argv, envs_make_envp(d->envs_hashmap));
		// execve(NULL, NULL, envs_make_envp(d->envs_hashmap));
	}
	exit(1);
}

void	exec_fork(t_ast *node, t_data *d)
{
	pid_t	pid;

	(void)node;
	(void)d;
	pid = fork();
	if (pid < 0)
	{
		// printf("ok\n");
	}
	else if (pid == 0)
	{
		// printf("ok\n");
		//pipefd NULLポインタだとintと型が合わない
		exec_child_process(node, NULL, d);
		// node->command_list;
	}
	else
	{
		node->command_list->pid = pid;
		// printf("parent process   %d\n", pid);
	}
	// return (0);
}

void	exec_wait_child_process(t_ast *node, t_data *d)
{
	int	status;

	waitpid(node->command_list->pid, &status, 0);
	d->exit_status = status;
}

void	exec_command(t_ast *node, t_operator operator, t_data *d)
{
	static size_t i = 0;

	exec_search_command(node, operator, d);
	i++;
	// printf("num   %zu\n", i);

	if (node->command_list != NULL)
	{
		exec_do_redirection(node, d);
		exec_fork(node, d);
	}
	// if (node->type == COMMAND)
	// {
	// 	bool	ret = do_redirection(node, &d);
	// 	if (ret == false && operator != LOGICAL_OR)
	// 	{
	// 		//エラー処理
	// 		//redirectionが失敗したらこのノードのコマンドを実行しない
	// 		//open readが失敗したときなど
	// 		return;
	// 	}
	// 	else if (ret == false && operator == LOGICAL_OR)//operator=LOGICAL_ORの場合、次のコマンドを実行
	// 	{
	// 		exec_wait_child_process(node);
	// 		exec_command(node->right_hand, operator, &d);
	// 	}
	// 	else if (operator == PIPE)
	// 		exec_pipe(node);
	// 	else if (operator == LOGICAL_AND)
	// 	{
	// 		if (exec_l_and(node))
	// 			exec_command(node->right_hand, operator, &d);
	// 	}
	// 	else if (operator == LOGICAL_OR)
	// 	{
	// 		if (exec_l_or(node));
	// 			exec_command(node->right_hand, operator, &d);
	// 	}
	// 	else if (operator == EXEC_START && exec_is_builtin(node))//operatorなしかつ実行するのはbuiltinのみなので、親プロセスで実行
	// 		return (builtin(node, NULL, &d));//builtin.hの関数
	// 	else
	// 		exec_fork(node, &d);
	// }
	if (operator == EXEC_START)
		exec_wait_child_process(node, d);
}

// int main(void)
// {
// 	extern const char **environ;
// 	t_data data;

// 	t_ast *node;
// 	t_ast *left_node;
// 	t_ast *right_node;

// 	t_word_list *word_list_left;
// 	t_word_list *word_list_right;

// 	t_redirect_list *redirect_list_left;
// 	t_redirect_list *redirect_list_right;

// 	word_list_left = debug_new_word_list("echo", 0, WORD);
// 	word_list_left->next = debug_new_word_list("$", 1, WORD);
// 	word_list_left->next->next = debug_new_word_list("\'", 1, TOKEN_SINGLE_QUOTE);
// 	word_list_left->next->next->next = debug_new_word_list("echo", 2, WORD);
// 	word_list_left->next->next->next->next = debug_new_word_list("\'", 6, TOKEN_SINGLE_QUOTE);
// 	word_list_left->next->next->next->next->next = debug_new_word_list("aaaa", 3, WORD);
// 	word_list_left->next->next->next->next->next->next = debug_new_word_list("bat", 3, WORD);

// 	redirect_list_left = debug_new_redirect_list("<", 2, PS_REDIRECTING_INPUT);
// 	redirect_list_left->next = debug_new_redirect_list("$out", 3, PS_FILE);

// 	left_node = debug_new_ast(debug_new_command(word_list_left, redirect_list_left), PS_COMMAND);
// 	;
// 	word_list_right = debug_new_word_list("echo", 1, WORD);
// 	word_list_right->next = debug_new_word_list("ok", 2, WORD);
// 	word_list_right->next->next = debug_new_word_list("$", 2, WORD);
// 	word_list_right->next->next->next = debug_new_word_list("\"", 2, TOKEN_DOUBLE_QUOTE);
// 	word_list_right->next->next->next->next = debug_new_word_list("$word", 2, WORD);
// 	word_list_right->next->next->next->next->next = debug_new_word_list("\"", 2, TOKEN_DOUBLE_QUOTE);

// 	redirect_list_right = debug_new_redirect_list(">", 3, PS_REDIRECTING_OUTPUT);
// 	redirect_list_right->next = debug_new_redirect_list("$PATH", 4, PS_FILE);

// 	right_node = debug_new_ast(debug_new_command(word_list_right, redirect_list_right), PS_COMMAND);

// 	node = debug_new_ast(NULL, PS_PIPE);
// 	node->left_hand = left_node;
// 	node->right_hand = right_node;

// 	data.exit_status = 0;
// 	envs_init(environ, &data);

// 	// debug_printf_double_arr(exec_change_word_list_to_double_arr(word_list_left));

// 	exec_command(node, EXEC_START, &data);
// 	// expansion(node, &data);

// 	// debug_printf_word_list(node->left_hand->command_list->word_list);
// 	// debug_printf_word_list(node->right_hand->command_list->word_list);

// 	// debug_printf_redirect(node->left_hand->command_list->redirect_list);
// 	// debug_printf_redirect(node->right_hand->command_list->redirect_list);

// 	// if (word_list_left == NULL)
// 	// 	printf("ok");
// 	// printf("%s\n", node->command_list->word_list->word);
// 	// debug_free_word_list(node->left_hand->command_list->word_list);
// 	// debug_free_word_list(node->right_hand->command_list->word_list);
// 	// debug_free_word_list(word_list_right);
// 	return (0);
// }