/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list_word_splitting.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:22:43 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/02 19:18:41 by tterao           ###   ########.fr       */
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

// t_word_list	*expand_new_null_word_list(t_word_list *next_node)
// {
// 	t_word_list	*new_word_list;

// 	new_word_list = try_malloc(sizeof(t_word_list));
// 	new_word_list->word = try_strdup("");
// 	new_word_list->type = NULL;
// 	new_word_list->tk_type = WORD;
// 	new_word_list->next = next_node;
// 	return (new_word_list);
// }

static size_t	get_next_index(char *word, char *type, char *ifs)
{
	size_t	i;

	i = 1;
	while (word[i] != '\0')
	{
		if (expand_is_str_in_char(ifs, word[i])
			&& !expand_is_quoted(type, i)
			&& IS_SUBSTITUTED == type[i] - '0')
			i++;
		else
			return (i);
	}
	return (0);
}

t_word_list	*expand_new_word_list_skip_ifs_char(char *word, char *type, char *ifs, t_word_list *next_node)
{
	t_word_list	*new_word_list;
	size_t		i;

	i = get_next_index(word, type, ifs);
	if (i == 0)
	{
		free(word);
		free(type);
		return (next_node);
	}
	new_word_list = try_malloc(sizeof(t_word_list));
	new_word_list->word = try_strdup(&word[i]);
	new_word_list->type = try_strdup(&type[i]);
	printf("if=%s\n", new_word_list->word);
	printf("if=%s\n", new_word_list->type);
	new_word_list->tk_type = WORD;
	new_word_list->next = next_node;
	free(word);
	free(type);
	return (new_word_list);
}

static void	expand_can_get_word_splitting_word_list(t_word_list *word_list,
														char *ifs, size_t i)
{
	char	*ifs_default_char;
	char	*word;
	char	*type;

	ifs_default_char = expand_check_ifs_default_char(ifs);
	word = word_list->word;
	type = word_list->type;
	if (i == 0)
	{
		// while (word[i] != '\0'
		// 	&& expand_is_str_in_char(ifs, word[i]))
		// {
		// 	if (!expand_is_str_in_char(ifs_default_char, word[i]))
		// 		word_list->next = expand_new_null_word_list(word_list->next);
		// 	(word_list->word)++;
		// 	(word_list->type)++;
		// 	i++;
		// }
		word_list->word = try_strdup("");
		word_list->type = NULL;
		word_list->next = expand_new_word_list_skip_ifs_char(word, type, ifs, word_list->next);
	}
	else
	{
		word_list->next = expand_new_word_list(word_list, i, word_list->next);
		word_list->word = try_substr(word, 0, i);
		word_list->type = try_substr(type, 0, i);
		printf("else=%s\n", word_list->word);
		printf("else=%s\n", word_list->type);
		free(word);
		free(type);
	}
	free(ifs_default_char);
}

void	expand_word_splitting_word_list(t_word_list *node, char *ifs)
{
	t_word_list	*word_list;
	size_t		i;

	i = 0;
	word_list = node;
	while (word_list->word[i] != '\0')
	{
		if (expand_is_str_in_char(ifs, word_list->word[i])
			&& !expand_is_quoted(word_list->type, i)
			&& IS_SUBSTITUTED == word_list->type[i] - '0')
		{
			expand_can_get_word_splitting_word_list(word_list, ifs, i);
			break ;
		}
		i++;
	}
	if (word_list->next != NULL && expand_have_ifs(word_list->next->word, ifs))
		expand_word_splitting_word_list(word_list->next, ifs);
}
