/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:20:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/11 15:02:56 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	expansion_search_node(t_ast *node, t_data *d)
{
	int ret;

	if (node->left_hand != NULL)
		ret = expansion(node->left_hand);
	if (ret)
		return;
	if (node->right_hand != NULL)
		ret = expansion(node->right_hand);
	if (ret)
		return;
	
}

int	expansion(t_ast *node, t_data **d)
{
	int	ret;

	expand_variable(node, *d);
	expand_word_splitting(node, d);
	expand_filename(node);
	expand_quotation(node);
	return (0);
}