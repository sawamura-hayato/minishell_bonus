/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:20:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/08 16:21:05 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 

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
	if (do_heredoc(node))
	{
		//signalの対応
		return (1);
	}
	expand_heredoc(node);
	return (0);
}