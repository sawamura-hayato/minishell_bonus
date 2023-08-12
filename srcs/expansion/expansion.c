/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:20:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/12 15:57:22 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	expansion(t_ast *node, t_data **d)
{
	if (node->left_hand != NULL)
		expansion(node->left_hand, d);
	if (node->right_hand != NULL)
		expansion(node->right_hand, d);
	expand_variable(node, *d);
	expand_word_splitting(node, d);
	expand_filename(node);
	expand_quotation(node);
	return (0);
}