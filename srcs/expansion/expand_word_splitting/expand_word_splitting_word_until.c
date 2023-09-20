/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting_word_until.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 05:45:36 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/20 11:35:54 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool		ft_is_c_in_str(char *str, char c);

bool	expand_is_all_ifs(char *word, char *ifs)
{
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0')
	{
		if (!ft_is_c_in_str(ifs, word[i]))
			return (false);
		i++;
	}
	return (true);
}

static t_word_list	*expand_new_null_word_list(t_word_list *next_node)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	new_word_list->word = try_strdup("");
	new_word_list->type = NULL;
	new_word_list->tk_type = WORD;
	new_word_list->next = next_node;
	return (new_word_list);
}

static void	expand_word_splitting_not_ifs_default_until(t_word_list **n,
				t_word_list **p, t_word_list **head)
{
	if (ft_strcmp((*n)->word, ""))
	{
		(*n)->word = try_strdup("");
		(*n)->type = NULL;
	}
	else if ((*p) == NULL)
	{
		(*head) = expand_new_null_word_list(*n);
		(*p) = (*head);
	}
	else
	{
		(*p)->next = expand_new_null_word_list(*n);
		(*p) = (*p)->next;
	}
}

void	expand_word_splitting_not_ifs_default(t_word_list **n, t_word_list **p,
												t_word_list **head, char *ifs)
{
	size_t	i;
	char	*de_ifs;
	char	*w;
	char	*t;

	i = 0;
	de_ifs = expand_check_ifs_default_char(ifs);
	w = (*n)->word;
	t = (*n)->type;
	while (w[i] != '\0' && t[i] == IS_SUBSTITUTED && ft_is_c_in_str(ifs, w[i]))
	{
		if (!ft_is_c_in_str(de_ifs, w[i]))
			expand_word_splitting_not_ifs_default_until(n, p, head);
		i++;
	}
	ft_all_free(w, t, de_ifs, NULL);
}

size_t	expand_get_index_word_splitting(t_word_list **n,
			t_word_list **p, t_word_list **head, char *ifs)
{
	size_t	i;
	char	*de_ifs;

	i = 0;
	de_ifs = expand_check_ifs_default_char(ifs);
	while ((*n)->word[i] != '\0' && (*n)->type[i] == IS_SUBSTITUTED
		&& ft_is_c_in_str(ifs, (*n)->word[i]))
	{
		if (!ft_is_c_in_str(de_ifs, (*n)->word[i]))
		{
			if ((*p) == NULL)
			{
				(*head) = expand_new_null_word_list(*n);
				(*p) = (*head);
			}
			else
			{
				(*p)->next = expand_new_null_word_list(*n);
				(*p) = (*p)->next;
			}
		}
		i++;
	}
	free(de_ifs);
	return (i);
}
