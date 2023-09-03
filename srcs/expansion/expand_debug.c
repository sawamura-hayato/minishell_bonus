/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:42:37 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/03 16:49:17 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "parse.h"

int	printf(const char *format, ...);

void	debug_bool_printf_test(bool flag, char *msg)
{
	static size_t i = 0;

	printf("[test: %zu]\n", i++);
	if (flag)
		printf("\e[0;32mok\033[0m: %s\n", msg);
	else
		printf("\e[0;31mko\033[0m: %s\n", msg);
}

void debug_printf_test(char *testA, char *testB)
{
	static size_t i = 0;

	printf("[test: %zu]\n", i++);
	if (testA != NULL && testB != NULL)
	{
		if (!ft_strcmp(testA, testB))
			printf("\e[0;32mok\033[0m\n");
		else
			printf("\e[0;31mko\033[0m\n");
	}
	else if (testA == NULL && testB == NULL)
		printf("\e[0;32mok\033[0m\n");
	else
		printf("\e[0;31mko\033[0m\n");
	printf("expect   %s\n", testA);
	printf("output   %s\n", testB);
}

void debug_printf_word_list(t_word_list *word_list)
{
	while (word_list != NULL)
	{
		printf("d word %s\n", word_list->word);
		printf("d type %s\n", word_list->type);
		word_list = word_list->next;
	}
}

void debug_free_word_list(t_word_list *word_list)
{
	// (void)word_list;
	t_word_list *tmp_word;

	if (word_list == NULL)
		return;
	tmp_word = word_list->next;
	while (tmp_word != NULL)
	{
		printf("word_list_free   %s\n", word_list->word);
		free(word_list);
		word_list = tmp_word;
		tmp_word = word_list->next;
	}
	printf("word_list_free   %s\n", word_list->word);
	free(word_list);
}

void debug_printf_redirect(t_redirect_list *redirect)
{
	while (redirect != NULL)
	{
		printf("redirect word   %s\n", redirect->word);
		printf("redirect type   %s\n", redirect->type);
		if (redirect->is_ambiguous_error)
			printf("ambiguous_error\n");
		redirect = redirect->next;
	}
}

void debug_free_redirect(t_redirect_list *redirect)
{
	// (void)redirect;
	t_redirect_list *tmp_word;

	if (redirect == NULL)
		return;
	tmp_word = redirect->next;
	while (tmp_word != NULL)
	{
		printf("redirect_free   %s\n", redirect->word);
		free(redirect);
		redirect = tmp_word;
		tmp_word = redirect->next;
	}
	printf("redirect_free   %s\n", redirect->word);
	free(redirect);
}

t_redirect_list *debug_new_redirect_list(char *word, size_t index,
t_redirect_type type)
{
	t_redirect_list *new_redirect_list;

	(void)index;
	new_redirect_list = try_malloc(sizeof(t_redirect_list));
	new_redirect_list->word = word;
	new_redirect_list->re_type = type;
	new_redirect_list->type = token_get_type_word(word, false);
	new_redirect_list->is_ambiguous_error = false;
	new_redirect_list->next = NULL;
	return (new_redirect_list);
}

t_word_list *debug_new_word_list(char *word, size_t index, t_token_type type)
{
	t_word_list *new_word_list;

	(void)index;
	new_word_list = try_malloc(sizeof(t_word_list));
	new_word_list->word = word;
	new_word_list->tk_type = type;
	new_word_list->type = token_get_type_word(word, false);
	new_word_list->next = NULL;
	return (new_word_list);
}

t_command *debug_new_command(t_word_list *word_list, 
t_redirect_list *redirect_list)
{
	t_command *new_command;

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
