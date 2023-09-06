/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect_list_word_splittitng.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:18:05 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/06 13:50:30 by hsawamur         ###   ########.fr       */
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

static void	expand_can_get_word_splitting_redirect(t_redirect_list **redirect,
														char *ifs, size_t i)
{
	t_redirect_list	*next;
	char			*word;
	char			*type;

	next = (*redirect)->next;
	word = (*redirect)->word;
	type = (*redirect)->type;
	if (i == 0)
	{
		while (word[i] != '\0' && 
			expand_is_str_in_char(ifs, word[i]))
			i++;
		(*redirect)->word = try_strdup(&(word[i]));
		(*redirect)->type = try_strdup(&(type[i]));
		free(word);
		free(type);
	}
	else
	{
		(*redirect)->next = expand_new_redirect_list((*redirect), i, next);
		(*redirect)->word = try_substr(word, 0, i);
		(*redirect)->type = try_substr(type, 0, i);
		free(word);
		free(type);
		(*redirect) = (*redirect)->next;
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
		if (expand_is_str_in_char(ifs, redirect_list->word[i]) && 
			!expand_is_quoted(redirect_list->type, i) && 
			IS_SUBSTITUTED == redirect_list->type[i])
		{
			expand_can_get_word_splitting_redirect(&redirect_list, ifs, i);
			break ;
		}
		i++;
	}
	if (redirect_list != NULL && 
		expand_is_word_splitting_word(redirect_list->word, 
										redirect_list->type, 
										ifs))
		expand_word_splitting_redirect_list(redirect_list, ifs);
}
