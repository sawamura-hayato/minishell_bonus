/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:20:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/13 20:03:15 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "parse.h"
#include "tokenize.h"

void	expansion(t_ast *node, t_data *d)
{
	if (node->left_hand != NULL)
		expansion(node->left_hand, d);
	if (node->right_hand != NULL)
		expansion(node->right_hand, d);
	expand_variable(node, d);
	// expand_word_splitting(node, d);
	// expand_filename(node);
	// expand_delete_quotation(node);
}

t_redirect	*debug_new_redirect_list(char *word, size_t index, t_redirect_type type)
{
	t_redirect	*new_redirect_list;

	new_redirect_list = try_malloc(sizeof(t_redirect));
	new_redirect_list->word = word;
	new_redirect_list->index = index;
	new_redirect_list->type = type;
	return (new_redirect_list);	
}

t_word_list	*debug_new_word_list(char *word, size_t index, t_token_type type)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	new_word_list->word = word;
	new_word_list->index = index;
	new_word_list->type = type;
	return (new_word_list);	
}

t_command	*debug_new_command(t_word_list *word_list, t_redirect *redirect_list)
{
	t_command	*new_command;

	new_command = try_malloc(sizeof(t_command));
	new_command->word_list = word_list;
	new_command->redirect_list = redirect_list;
	return (new_command);	
}

t_ast	*debug_new_ast(t_command *command, t_ast_node_type type)
{
	t_ast	*new_ast;

	new_ast = try_malloc(sizeof(t_ast));
	new_ast->command_list = command;
	new_ast->type = type;
	new_ast->left_hand = NULL;
	new_ast->right_hand = NULL;
	return (new_ast);	
}

int main(void)
{
	extern const char **environ;
	t_data	data;
	
	t_ast	*node;
	t_ast	*left_node;
	t_ast	*right_node;

	t_word_list	*word_list;
	t_redirect 	*redirect_list;

	word_list = debug_new_word_list("echo", 0, WORD);
	word_list->next = debug_new_word_list("aaaa", 1, WORD);
	// word_list = word_list->next;

	redirect_list = debug_new_redirect_list("<", 2, REDIRECTING_INPUT);
	redirect_list->next = debug_new_redirect_list("out", 3, FILE);

	left_node = debug_new_ast(debug_new_command(word_list, redirect_list), COMMAND);
	right_node = debug_new_ast(debug_new_command(word_list, redirect_list), COMMAND);
	
	node = debug_new_ast(NULL, (t_ast_node_type)PIPE);
	node->left_hand = left_node;
	node->right_hand = right_node;

	data.exit_status = 0;
	envs_init(environ, &data);
	expansion(node, &data);
	return (0);
}
