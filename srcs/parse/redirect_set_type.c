/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_set_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:36:13 by tterao            #+#    #+#             */
/*   Updated: 2023/08/28 19:01:10 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	redirect_set_type_word(t_redirect_list *last_node,
		t_redirect_list *node, t_token *token)
{
	t_redirect_type	type;

	type = last_node->re_type;
	if (token->tk_type != WORD)
	{
		node->re_type = -1;
		return ;
	}
	if (type == PS_REDIRECTING_INPUT || type == PS_REDIRECTING_OUTPUT
		|| type == PS_APPENDING_OUTPUT)
		node->re_type = PS_FILE;
	else if (type == PS_HERE_DOCUMENTS)
	{
		if ((ft_strrchr(token->type, IS_SINGLE_QUOTED + '0') != NULL)
			|| ft_strrchr(token->type, IS_DOUBLE_QUOTED + '0') != NULL)
			node->re_type = PS_QUOTE_DELIMITER;
		else
			node->re_type = PS_DELIMITER;
	}
}

bool	is_redirect_operator(t_redirect_list *node)
{
	return (node->re_type == PS_REDIRECTING_INPUT
		|| node->re_type == PS_REDIRECTING_OUTPUT
		|| node->re_type == PS_APPENDING_OUTPUT
		|| node->re_type == PS_HERE_DOCUMENTS);
}

void	redirect_set_type(t_redirect_list **head, t_redirect_list *node,
		t_token *token)
{
	t_redirect_list	*last_node;

	last_node = redirect_list_get_last_node(head);
	if (last_node != NULL && is_redirect_operator(last_node))
		return (redirect_set_type_word(last_node, node, token));
	if (ft_strcmp(token->word, "<") == 0)
		node->re_type = PS_REDIRECTING_INPUT;
	else if (ft_strcmp(token->word, ">") == 0)
		node->re_type = PS_REDIRECTING_OUTPUT;
	else if (ft_strcmp(token->word, ">>") == 0)
		node->re_type = PS_APPENDING_OUTPUT;
	else if (ft_strcmp(token->word, "<<") == 0)
		node->re_type = PS_HERE_DOCUMENTS;
}
