/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_set_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:36:13 by tterao            #+#    #+#             */
/*   Updated: 2023/08/21 20:22:01 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	redirect_set_type_word(t_redirect_list *last_node, t_redirect_list*node, t_token *token)
{
	const t_redirect_type	type = last_node->type;

	// printf("last_node:%s\n",last_node->word);
	// printf("token:%s\n",token->word);
	(void)token;
	if (type == PS_REDIRECTING_INPUT || type == PS_REDIRECTING_OUTPUT
		|| type == PS_APPENDING_OUTPUT)
		node->type = PS_FILE;
	else if (type == PS_HERE_DOCUMENTS)
		node->type = PS_DELIMITER;
}

static bool	is_redirect_operator(t_redirect_list *node)
{
	return (node->type == PS_REDIRECTING_INPUT
		|| node->type == PS_REDIRECTING_OUTPUT
		|| node->type == PS_APPENDING_OUTPUT
		|| node->type == PS_HERE_DOCUMENTS);
}

// static t_redirect_list	*reirect_get_prenode(t_redirect_list **head, t_redirect_list *target)
// {
// 	t_redirect_list	*node;

// 	node = *head;
// 	while (node != NULL)
// 	{
// 		if (node->next == target)
// 			return (node);
// 		node = node->next;
// 	}
// 	return (NULL);
// }

// static bool	is_quotation(t_redirect_list *node)
// {
// 	return (node->type == PS_REDIRECT_SINGLE_QUOTE
// 		|| node->type == PS_REDIRECT_DOUBLE_QUOTE);
// }

void	redirect_set_type(t_redirect_list **head, t_redirect_list *node, t_token *token)
{
	t_redirect_list	*last_node;
	// t_redirect_list	*prenode;

	last_node = redirect_list_get_last_node(head);
	// prenode = reirect_get_prenode(head, last_node);
	if (last_node != NULL && is_redirect_operator(last_node))
		return (redirect_set_type_word(last_node, node, token));
	if (ft_strcmp(token->word, "<") == 0)
		node->type = PS_REDIRECTING_INPUT;
	else if (ft_strcmp(token->word, ">") == 0)
		node->type = PS_REDIRECTING_OUTPUT;
	else if (ft_strcmp(token->word, ">>") == 0)
		node->type = PS_APPENDING_OUTPUT;
	else if (ft_strcmp(token->word, "<<") == 0)
		node->type = PS_HERE_DOCUMENTS;
}
