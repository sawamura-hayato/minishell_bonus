/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect_list_word_splittitng.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:18:05 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/20 11:34:27 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

bool	expand_is_all_ifs(char *word, char *ifs);
bool	ft_is_c_in_str(char *str, char c);

t_redirect_list	*expand_new_redirect_list(t_redirect_list *node, size_t i,
											t_redirect_list *next_node,
											char *ifs)
{
	t_redirect_list	*new_redirect_list;
	char			*next_word;
	char			*next_type;

	new_redirect_list = try_malloc(sizeof(t_redirect_list));
	i++;
	next_word = try_strdup(&(node->word[i]));
	next_type = try_strdup(&(node->type[i]));
	if (expand_is_all_ifs(next_word, ifs))
	{
		new_redirect_list->word = NULL;
		new_redirect_list->type = NULL;
		free(next_word);
		free(next_type);
	}
	else
	{
		new_redirect_list->word = next_word;
		new_redirect_list->type = next_type;
	}
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
		while (word[i] != '\0' && \
				type[i] == IS_SUBSTITUTED && \
				ft_is_c_in_str(ifs, word[i]))
			i++;
		(*redirect)->word = try_strdup(&(word[i]));
		(*redirect)->type = try_strdup(&(type[i]));
	}
	else
	{
		(*redirect)->next = expand_new_redirect_list((*redirect), i, next, ifs);
		(*redirect)->word = try_substr(word, 0, i);
		(*redirect)->type = try_substr(type, 0, i);
		(*redirect) = (*redirect)->next;
	}
	free(word);
	free(type);
}

void	expand_word_splitting_redirect_list(t_redirect_list *node, char *ifs)
{
	t_redirect_list	*redirect_list;
	size_t			i;

	i = 0;
	redirect_list = node;
	while (redirect_list->word[i] != '\0')
	{
		if (ft_is_c_in_str(ifs, redirect_list->word[i]) && \
			!expand_is_quoted(redirect_list->type, i) && \
			IS_SUBSTITUTED == redirect_list->type[i])
		{
			expand_can_get_word_splitting_redirect(&redirect_list, ifs, i);
			break ;
		}
		i++;
	}
	if (expand_is_word_splitting_word(redirect_list->word, \
										redirect_list->type, ifs))
		expand_word_splitting_redirect_list(redirect_list, ifs);
}
