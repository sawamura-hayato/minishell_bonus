/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:30:36 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/08 16:44:02 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	expand_splitting_word_list(t_word_list *word_list, t_envs *ifs)
{
	
}

void	expand_splitting_redirect_list(t_redirect *redirect_list, t_envs *ifs)
{
	
}

void	expand_word_splitting(t_ast *node, t_data *d)
{
	t_envs	*ifs;

	ifs = get_target_value(d->envs_hashmap, "IFS");
	expand_splitting_word_list(node->command_list->word_list, ifs);
	expand_splitting_redirect_list(node->command_list->word_list, ifs);
	
}