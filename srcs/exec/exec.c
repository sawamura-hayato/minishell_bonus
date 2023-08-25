/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:01 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/25 11:36:20 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include "builtins.h"

static t_operator	exec_change_ast_type_to_operator(t_ast_node_type ast_type)
{
	if (PS_PIPE == ast_type)
		return (EXEC_PIPE);
	else if (PS_LOGICAL_AND == ast_type)
		return (EXEC_LOGICAL_AND);
	else if (PS_LOGICAL_OR == ast_type)
		return (EXEC_LOGICAL_OR);
	return (EXEC_START);
}

static void	exec_search_command(t_ast *node, t_operator operator, t_data *d)
{

	if (node->left_hand != NULL)
		exec_command(node->left_hand,
			exec_change_ast_type_to_operator(node->type), d);
	else if (node->type == PS_LOGICAL_AND)
	{
		exec_wait_child_process(node->left_hand, d);
		if (d->exit_status == EXIT_SUCCESS)
			exec_command(node->right_hand, operator, d);
	}
	else if (node->type == PS_LOGICAL_OR)
	{
		exec_wait_child_process(node->left_hand, d);
		if (d->exit_status != EXIT_SUCCESS)
			exec_command(node->right_hand, operator, d);
	}
	else if (operator == EXEC_START && node->right_hand != NULL)
		exec_command(node->right_hand, EXEC_END, d);
	else if (node->right_hand != NULL)
		exec_command(node->right_hand, operator, d);
}

/**
 * @brief この関数は、コマンドがbuiltinか判定する
 *
 * node->command_list->word_listがbuiltinか判定する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true builtinの場合、trueを返す
 * @return false builtinde出ない場合、falseを返す
 */
bool	exec_is_builtin(t_ast *node)
{
	char	*command;

	if (node->command_list->word_list == NULL)
		return (false);
	command = node->command_list->word_list->word;
	return (
		ft_strcmp_ignorecase(command, "echo") == 0
		|| ft_strcmp_ignorecase(command, "cd") == 0
		|| ft_strcmp_ignorecase(command, "pwd") == 0
		|| ft_strcmp_ignorecase(command, "export") == 0
		|| ft_strcmp_ignorecase(command, "unset") == 0
		|| ft_strcmp_ignorecase(command, "env") == 0
		|| ft_strcmp_ignorecase(command, "exit") == 0
	);
}

/**
 * @brief この関数はコマンドを実行する
 *
 * 第一引数の構文木nodeのタイプがコマンドの場合、node->command_listをコマンドとして、実行する
 * 第二引数のoperatorはコマンドの出力先を指定する。left_handにはnode->typeを渡し、right_handには上のnodeから引き継いだoperatorを渡す
 * 一番初めのnode（初めにcommand_executionを呼ぶとき）は、operatorはEXEC_STARTになる
 * 一番最後に実行されるnodeのoperatorはEXEC_ENDになる
 * 第三引数のdは環境変数と終了ステータスを管理する
 *
 * @param node 構文木のnode
 * @param operator 構文木nodeの一つ上のnodeから引き継ぐoperator
 * @param d 環境変数と終了ステータス
 */
void	exec_command(t_ast *node, t_operator operator, t_data *d)
{
	exec_search_command(node, operator, d);
	// if (node->command_list != NULL)
	// {
	// 	exec_do_redirection(node, d);
	// 	exec_fork(node, d);
	// }
	if (node->type == PS_COMMAND)
	{
		if (exec_do_redirection(node, d) == false)
			return ;
		else if (operator == EXEC_PIPE)
			exec_pipe(node, d);
		else if (operator == EXEC_START && exec_is_builtin(node))
			return (builtin(node, NULL, d));
		else
			exec_fork(node, d);
	}
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