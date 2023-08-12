/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_delete_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:39:09 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/12 15:55:05 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	word_list_delete_target_type(t_word_list *word_list, t_token_type taget);
void	redirect_list_delete_target_type(t_word_list *word_list, t_token_type taget);

void	expandion_delete_quotation_word_list(t_word_list *word_list)
{
	word_list_delete_target(word_list, SINGLE_QUOTE);
	word_list_delete_target(word_list, DOUBLE_QUOTE);
}

void	expandion_delete_quotation_redirect_list(t_redirect *redirect_list)
{
	redirect_list_delete_target(redirect_list, SINGLE_QUOTE);
	redirect_list_delete_target(redirect_list, DOUBLE_QUOTE);
}

void	expand_delete_quotation(t_ast *node)
{
	expandion_delete_quotation_word_list(node->command_list->word_list);
	expandion_delete_quotation_redirect_list(node->command_list->redirect_list);
}
