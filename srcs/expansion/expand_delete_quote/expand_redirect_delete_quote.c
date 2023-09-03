/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect_delete_quote.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:51:01 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/03 20:10:55 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	expand_delete_quotation_redirect_until(t_redirect_list *redirect, 
													char **new_word, 
													char **new_type)
{
	size_t	i;
	size_t	new_index;
	bool	is_in_quote;
	
	i = 0;
	new_index = 0;
	is_in_quote = false;
	while (redirect->type[i] != '\0')
	{
		if (!expand_is_type_quotation(redirect->type[i]))
		{
			(*new_word)[new_index] = redirect->word[i];
			if (is_in_quote)
				(*new_type)[new_index] = IS_IN_QUOTED;
			else
				(*new_type)[new_index] = redirect->type[i];
			new_index++;
		}
		else
			is_in_quote = !is_in_quote;
		i++;
	}
}

void	expand_delete_quotation_redirect_list(t_redirect_list *redirect_list)
{
	char	*new_word;
	char	*new_type;
	size_t	size;

	size = expand_get_size_delete_quotation_word(redirect_list->type);
	new_word = try_calloc(size + 1, sizeof(char));
	new_type = try_calloc(size + 1, sizeof(char));
	expand_delete_quotation_redirect_until(redirect_list, &new_word, &new_type);
	free(redirect_list->word);
	free(redirect_list->type);
	redirect_list->word = new_word;
	redirect_list->type = new_type;
}
