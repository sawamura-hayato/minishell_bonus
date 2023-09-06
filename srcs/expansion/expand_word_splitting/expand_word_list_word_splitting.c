/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list_word_splitting.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:22:43 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/06 13:34:04 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

t_word_list	*expand_new_word_list(t_word_list *node, size_t i,
									t_word_list *next_node)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	i++;
	new_word_list->word = try_strdup(&(node->word[i]));
	new_word_list->type = try_strdup(&(node->type[i]));
	new_word_list->tk_type = WORD;
	new_word_list->next = next_node;
	return (new_word_list);
}

t_word_list	*expand_new_null_word_list(t_word_list *next_node)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	new_word_list->word = try_strdup("");
	new_word_list->type = NULL;
	new_word_list->tk_type = WORD;
	new_word_list->next = next_node;
	return (new_word_list);
}

static void	expand_can_get_word_splitting_word_list(t_word_list **word_list,
													char *ifs, size_t i)
{
	t_word_list	*next;
	char		*word;
	char		*type;

	next = (*word_list)->next;
	word = (*word_list)->word;
	type = (*word_list)->type;
	if (i == 0)
	{
		while (word[i] != '\0' && 
				expand_is_str_in_char(ifs, word[i]))
			i++;
		(*word_list)->word = try_strdup(&(word[i]));
		(*word_list)->type = try_strdup(&(type[i]));
		free(word);
		free(type);
	}
	else
	{
		(*word_list)->next = expand_new_word_list((*word_list), i, next);
		(*word_list)->word = try_substr(word, 0, i);
		(*word_list)->type = try_substr(type, 0, i);
		free(word);
		free(type);
		(*word_list) = (*word_list)->next;
	}
}

void	expand_word_splitting_word_list(t_word_list *node, char *ifs)
{
	t_word_list	*word_list;
	size_t		i;

	i = 0;
	word_list = node;
	while (word_list->word[i] != '\0')
	{
		if (expand_is_str_in_char(ifs, word_list->word[i]) && 
			!expand_is_quoted(word_list->type, i) && 
			IS_SUBSTITUTED == word_list->type[i])
		{
			expand_can_get_word_splitting_word_list(&word_list, ifs, i);
			break ;
		}
		i++;
	}
	if (word_list != NULL && expand_is_word_splitting_word(word_list->word, 
															word_list->type, 
															ifs))
		expand_word_splitting_word_list(word_list, ifs);
}
