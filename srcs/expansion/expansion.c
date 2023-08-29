/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:20:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/29 23:04:30 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "parse.h"
#include "tokenize.h"

int printf(const char *format, ...);

void	expand_command_list(t_ast *node, t_data *d)
{
	expand_word_list(&(node->command_list->word_list), d);
	expand_redirect_list(&(node->command_list->redirect_list), d);
}


void expansion(t_ast *node, t_data *d)
{
	if (node->left_hand != NULL)
		expansion(node->left_hand, d);
	if (node->right_hand != NULL)
		expansion(node->right_hand, d);
	if (node->command_list != NULL)
		expand_command_list(node, d);
	else
		printf("operator\n");
}

int main(void)
{
	extern const char **environ;
	t_data	data;

	t_ast	*node;
	t_ast	*left_node;
	t_ast	*right_node;

	t_word_list	*word_list_left;
	t_word_list	*word_list_right;

	t_redirect_list 	*redirect_list_left;
	t_redirect_list 	*redirect_list_right;

	//クウォートがある場合の対応
	//記号対応
	word_list_left = NULL;
	// word_list_left = debug_new_word_list("$\'$A\'", 0, WORD);
	word_list_new_tail(&word_list_left, debug_new_word_list("\"$A\"", 0, WORD));
	word_list_new_tail(&word_list_left, debug_new_word_list("$A\"dddd\"", 0, WORD));
	word_list_new_tail(&word_list_left, debug_new_word_list("$\"$A\"", 0, WORD));
	word_list_new_tail(&word_list_left, debug_new_word_list("$\'$A\'", 0, WORD));
	word_list_new_tail(&word_list_left, debug_new_word_list("\'gg$A\'++++\'$Agg\'", 1, WORD));
	word_list_new_tail(&word_list_left, debug_new_word_list("$Agg--??gg$A", 1, WORD));
	// word_list_new_tail(&word_list_left, debug_new_word_list("$aaaa", 1, WORD));
	// word_list_new_tail(&word_list_left, debug_new_word_list("bat", 1, WORD));
	// word_list_new_tail(&word_list_left, debug_new_word_list("\"$Agg\"\"gg$A\"", 1, WORD));

	redirect_list_left = debug_new_redirect_list("<", 2, PS_REDIRECTING_INPUT);
	redirect_list_left->next = debug_new_redirect_list("$out", 3, PS_FILE);

	left_node = debug_new_ast(debug_new_command(word_list_left, redirect_list_left), PS_COMMAND);
	;
	word_list_right = debug_new_word_list("echo", 0, WORD);
	word_list_new_tail(&word_list_right, debug_new_word_list("ok$", 0, WORD));
	word_list_new_tail(&word_list_right, debug_new_word_list("$", 1, WORD));
	word_list_new_tail(&word_list_right, debug_new_word_list("$?", 2, WORD));

	// word_list_right->next->next->next = debug_new_word_list("\"", 2, TOKEN_DOUBLE_QUOTE);
	// word_list_right->next->next->next->next->next = debug_new_word_list("\"", 2, TOKEN_DOUBLE_QUOTE);

	// redirect_list_right->next->next = debug_new_redirect_list("$PATH", 4, PS_FILE);


	data.exit_status = 0;
	envs_init(environ, &data);
	redirect_list_right = debug_new_redirect_list(">", 3, PS_REDIRECTING_OUTPUT);
	redirect_list_right->next = debug_new_redirect_list("$A\"$A\"", 4, PS_FILE);
	redirect_list_right->next->next = debug_new_redirect_list("$A\"$A\"\"$A\"", 5, PS_DELIMITER);
	right_node = debug_new_ast(debug_new_command(word_list_right, redirect_list_right), PS_COMMAND);

	node = debug_new_ast(NULL, PS_PIPE);
	node->left_hand = left_node;
	node->right_hand = right_node;
	expansion(node, &data);

	debug_printf_word_list(node->left_hand->command_list->word_list);
	// debug_printf_word_list(node->right_hand->command_list->word_list);

	// debug_printf_redirect(node->left_hand->command_list->redirect_list);
	// debug_printf_redirect(node->right_hand->command_list->redirect_list);
	// if (word_list_left == NULL)
	// 	printf("ok");
	// printf("%s\n", node->command_list->word_list->word);
	// debug_free_word_list(node->left_hand->command_list->word_list);
	// debug_free_word_list(node->right_hand->command_list->word_list);
	// debug_free_word_list(word_list_right);
	return (0);
}
