/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:20:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/11 16:12:37 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "parse.h"
#include "tokenize.h"

void	expand_command_list(t_ast *node, t_data *d)
{
	expand_word_list(&(node->command_list->word_list), d);
	expand_redirect_list(&(node->command_list->redirect_list), d);
}

void	expansion_ast_l2(t_ast *node, t_data *d)
{
	if (node->left_hand != NULL)
		expansion_ast_l2(node->left_hand, d);
	if (node->right_hand != NULL)
		expansion_ast_l2(node->right_hand, d);
	if (node->command_list != NULL)
		expand_command_list(node, d);
}

void	expansion(t_ast_l1 *node, t_data *d)
{
	if (node->left_hand != NULL)
		expansion(node->left_hand, d);
	if (node->right_hand != NULL)
		expansion(node->right_hand, d);
	if (node->ast != NULL)
		expansion_ast_l2(node->ast, d);
}
