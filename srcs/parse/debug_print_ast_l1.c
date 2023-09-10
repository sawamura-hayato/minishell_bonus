/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_ast_l1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:00:34 by tterao            #+#    #+#             */
/*   Updated: 2023/09/10 20:32:26 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	debug_print_ast_l1(t_ast_l1 *node)
{
	if (node == NULL)
		return ;
	if (node->left_hand != NULL)
		debug_print_ast_l1(node->left_hand);
	if (node->right_hand != NULL)
		debug_print_ast_l1(node->right_hand);
	if (node->type == AST_COMMAND)
		return (debug_print_ast(node->ast));
	if (node->type == AST_LOGICAL_AND)
		printf("&&\n");
	else if (node->type == AST_LOGICAL_OR)
		printf("||\n");
	printf("==========================\n\n");
}
