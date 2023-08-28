/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:59:35 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/27 22:59:49 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

void	debug_print_ast(t_ast *node)
{
	t_redirect_list	*redirect_p;
	t_word_list		*word_p;

	if (node == NULL)
	{
		printf("ast_node is NULL\n");
		return ;
	}
	if (node->left_hand != NULL)
		debug_print_ast(node->left_hand);
	if (node->right_hand != NULL)
		debug_print_ast(node->right_hand);
	printf("===========debug==================\n");
	printf("ast_node_type:[%d]\n", node->type);
	if (node->command_list == NULL)
		return ;
	word_p = node->command_list->word_list;
	if (word_p == NULL)
		printf("NULL word_list%p\n", word_p);
	redirect_p = node->command_list->redirect_list;
	if (redirect_p == NULL)
		printf("NULL redirect_list%p\n", redirect_p);
	while (word_p != NULL)
	{
		printf("word_list:[%s] ", word_p->word);
		printf("type:[%d]\n", word_p->tk_type);
		word_p = word_p->next;
	}
	while (redirect_p != NULL)
	{
		printf("redirect_list:[%s] ", redirect_p->word);
		printf("type:[%d]\n", redirect_p->re_type);
		redirect_p = redirect_p->next;
	}
	printf("===========debug==================\n");
}
