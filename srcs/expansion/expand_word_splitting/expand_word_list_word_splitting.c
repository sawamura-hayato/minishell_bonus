/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list_word_splitting.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:22:43 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/19 21:39:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

bool	expand_is_all_ifs(char *word, char *ifs)
{
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0')
	{
		if (!expand_is_str_in_char(ifs, word[i]))
			return (false);
		i++;
	}
	return (true);
}

static size_t	expand_check_index_not_ifs_default(t_word_list *node, size_t i, char *ifs)
{
	char	*de_ifs;

	de_ifs = expand_check_ifs_default_char(ifs);
	while (node->word[i] != '\0' && node->type[i] == IS_SUBSTITUTED && expand_is_str_in_char(ifs, node->word[i]))
	{
		if (!expand_is_str_in_char(de_ifs, node->word[i]))
		{
			i++;
			free(de_ifs);
			return (i);
		}
		i++;
	}
	free(de_ifs);
	return (i);
}

static t_word_list	*expand_new_word_list(t_word_list *node, size_t i, \
									t_word_list *next_node, char *ifs)
{
	t_word_list	*new_word_list;
	char		*next_word;
	char		*next_type;

	new_word_list = try_malloc(sizeof(t_word_list));
	i = expand_check_index_not_ifs_default(node, i, ifs);
	next_word = try_strdup(&(node->word[i]));
	next_type = try_strdup(&(node->type[i]));
	new_word_list->word = next_word;
	new_word_list->type = next_type;
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

void	expand_word_splitting_not_ifs_default(t_word_list **node, t_word_list **pre_node, t_word_list **word_list, char *ifs)
{
	size_t	i;
	char	*de_ifs;
	char	*word;
	char	*type;

	i = 0;
	de_ifs = expand_check_ifs_default_char(ifs);
	word = try_strdup((*node)->word);
	type = try_strdup((*node)->type);
	while (word[i] != '\0' && \
			type[i] == IS_SUBSTITUTED && \
			expand_is_str_in_char(ifs, word[i]))
	{
		if (!expand_is_str_in_char(de_ifs, word[i]))
		{
			if (ft_strcmp((*node)->word, ""))
			{
				(*node)->word = try_strdup("");
				(*node)->type = NULL;
			}
			else if ((*pre_node) == NULL)
			{
				(*word_list) =  expand_new_null_word_list(*node);
				(*pre_node) = (*word_list);
			}
			else
			{
				(*pre_node)->next = expand_new_null_word_list(*node);
				(*pre_node) = (*pre_node)->next;
			}
		}
		i++;
	}
	free(de_ifs);
	free(word);
	free(type);
}

size_t	expand_get_index_word_splitting(t_word_list **node, t_word_list **pre_node, t_word_list **word_list, char *ifs)
{
	size_t	i;
	char	*de_ifs;

	i = 0;
	de_ifs = expand_check_ifs_default_char(ifs);
	while ((*node)->word[i] != '\0' && \
			(*node)->type[i] == IS_SUBSTITUTED && \
			expand_is_str_in_char(ifs, (*node)->word[i]))
	{
		if (!expand_is_str_in_char(de_ifs, (*node)->word[i]))
		{
			if ((*pre_node) == NULL)
			{
				(*word_list) =  expand_new_null_word_list(*node);
				(*pre_node) = (*word_list);
			}
			else
			{
				(*pre_node)->next = expand_new_null_word_list(*node);
				(*pre_node) = (*pre_node)->next;
			}
		}
		i++;
	}
	free(de_ifs);
	return (i);
}

static void expand_set_word_splitting_word_list(t_word_list **node,
												t_word_list **pre_node,
												t_word_list **word_list, char *ifs)
{
	size_t		i;
	char		*word;
	char		*type;

	word = (*node)->word;
	type = (*node)->type;
	i = expand_get_index_word_splitting(node, pre_node, word_list, ifs);
	(*node)->word = try_strdup(&(word[i]));
	(*node)->type = try_strdup(&(type[i]));
	free(word);
	free(type);
}

static void	expand_get_word_splitting_word_list(t_word_list **node,
												size_t i, char *ifs)
{
	t_word_list	*next;
	char		*word;
	char		*type;

	next = (*node)->next;
	word = (*node)->word;
	type = (*node)->type;
	(*node)->next = expand_new_word_list((*node), i, next, ifs);
	(*node)->word = try_substr(word, 0, i);
	(*node)->type = try_substr(type, 0, i);
	free(word);
	free(type);
}


void	expand_word_splitting_word_list(t_word_list *node, t_word_list *pre_node, t_word_list **word_list, char *ifs)
{
	size_t		i;

	i = 0;
	
	while (node->word[i] != '\0')
	{
		if (expand_is_str_in_char(ifs, node->word[i]) && \
			!expand_is_quoted(node->type, i) && \
			IS_SUBSTITUTED == node->type[i])
		{
			if (i == 0)
				expand_set_word_splitting_word_list(&node, &pre_node, word_list, ifs);
			else
			{
				expand_get_word_splitting_word_list(&node, i, ifs);
				pre_node = node;
				node = node->next;
			}
			break ;
		}
		i++;
	}
	if (expand_is_word_splitting_word(node->word, node->type, ifs))
		expand_word_splitting_word_list(node, pre_node, word_list, ifs);
	else if (expand_is_all_ifs(node->word, ifs))
	{
		expand_get_index_word_splitting(&node, &pre_node, word_list, ifs);
		word_list_delete_target(&pre_node, node);
	}
}
