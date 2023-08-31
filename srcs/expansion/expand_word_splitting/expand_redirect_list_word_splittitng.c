/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect_list_word_splittitng.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:18:05 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 09:50:53 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

t_redirect_list	*expand_new_redirect_list(t_redirect_list *node,
											size_t i,
											t_redirect_list *next_node)
{
	t_redirect_list	*new_redirect_list;

	new_redirect_list = try_malloc(sizeof(t_redirect_list));
	i++;
	new_redirect_list->word = try_strdup(&(node->word[i]));
	new_redirect_list->type = try_strdup(&(node->type[i]));
	new_redirect_list->re_type = PS_FILE;
	new_redirect_list->next = next_node;
	return (new_redirect_list);
}

t_redirect_list	*expand_new_null_redirect_list(t_redirect_list *next_node)
{
	t_redirect_list	*new_redirect_list;

	new_redirect_list = try_malloc(sizeof(t_redirect_list));
	new_redirect_list->word = try_strdup("");
	new_redirect_list->type = NULL;
	new_redirect_list->re_type = PS_FILE;
	new_redirect_list->next = next_node;
	return (new_redirect_list);
}

static void	expand_can_get_word_splitting_redirect(t_redirect_list *redirect,
														char *ifs, size_t i)
{
	char	*ifs_default_char;

	ifs_default_char = expand_check_ifs_default_char(ifs);
	if (i == 0)
	{
		while (redirect->word[i] != '\0' && \
				!expand_is_str_in_char(ifs, redirect->word[i]))
		{
			if (!expand_is_str_in_char(ifs_default_char, redirect->word[i]))
				redirect->next = expand_new_null_redirect_list(redirect->next);
			i++;
		}
	}
	else
	{
		redirect->next = expand_new_redirect_list(redirect, i, redirect->next);
		redirect->word = try_substr(redirect->word, 0, i);
		redirect->type = try_substr(redirect->type, 0, i);
	}
}

void	expand_word_splitting_redirect_list(t_redirect_list *node, char *ifs)
{
	t_redirect_list	*redirect_list;
	size_t			i;

	i = 0;
	redirect_list = node;
	while (redirect_list->word[i] != '\0')
	{
		if (expand_is_str_in_char(ifs, redirect_list->word[i]) && \
			!expand_is_quoted(redirect_list->type, i) && \
			redirect_list->type[i] == '1')
		{
			expand_can_get_word_splitting_redirect(redirect_list, ifs, i);
			break ;
		}
		i++;
	}
	if (expand_have_ifs(redirect_list->next->word, ifs))
		expand_word_splitting_redirect_list(redirect_list->next, ifs);
}
