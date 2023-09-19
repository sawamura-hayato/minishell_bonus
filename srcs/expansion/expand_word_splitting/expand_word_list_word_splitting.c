/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list_word_splitting.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:22:43 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/20 05:57:19 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

bool	ft_is_str_in_c(char *str, char c);
bool	expand_is_all_ifs(char *word, char *ifs);
void	expand_word_splitting_not_ifs_default(t_word_list **n, t_word_list **p,
			t_word_list **head, char *ifs);
size_t	expand_get_index_word_splitting(t_word_list **n, t_word_list **p,
			t_word_list **head, char *ifs);

static size_t	expand_check_index_not_ifs_default(t_word_list *node,
													size_t i, char *ifs)
{
	char	*de_ifs;

	de_ifs = expand_check_ifs_default_char(ifs);
	while (node->word[i] != '\0' && \
			node->type[i] == IS_SUBSTITUTED && \
			ft_is_str_in_c(ifs, node->word[i]))
	{
		if (!ft_is_str_in_c(de_ifs, node->word[i]))
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

static void	expand_set_word_splitting_word_list(t_word_list **node,
				t_word_list **pre_node, t_word_list **word_list, char *ifs)
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

static void	expand_get_word_splitting_word_list(t_word_list **n,
				t_word_list **p, size_t i, char *ifs)
{
	t_word_list	*next;
	char		*word;
	char		*type;

	next = (*n)->next;
	word = (*n)->word;
	type = (*n)->type;
	(*n)->next = expand_new_word_list((*n), i, next, ifs);
	(*n)->word = try_substr(word, 0, i);
	(*n)->type = try_substr(type, 0, i);
	*p = *n;
	*n = (*n)->next;
	free(word);
	free(type);
}

void	expand_word_splitting_word_list(t_word_list *n, t_word_list *p,
			t_word_list **head, char *ifs)
{
	size_t		i;

	i = 0;
	while (n->word[i] != '\0')
	{
		if (ft_is_str_in_c(ifs, n->word[i]) && !expand_is_quoted(n->type, i)
			&& IS_SUBSTITUTED == n->type[i])
		{
			if (i == 0)
				expand_set_word_splitting_word_list(&n, &p, head, ifs);
			else
				expand_get_word_splitting_word_list(&n, &p, i, ifs);
			break ;
		}
		i++;
	}
	if (expand_is_word_splitting_word(n->word, n->type, ifs))
		expand_word_splitting_word_list(n, p, head, ifs);
	else if (expand_is_all_ifs(n->word, ifs))
	{
		expand_get_index_word_splitting(&n, &p, head, ifs);
		word_list_delete_target(&p, n);
	}
}
