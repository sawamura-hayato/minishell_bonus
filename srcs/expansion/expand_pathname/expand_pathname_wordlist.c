/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname_wordlist.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:21:07 by tterao            #+#    #+#             */
/*   Updated: 2023/09/04 18:23:55 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"
#include <sys/types.h>
#include <dirent.h>

t_word_list	*expand_star_wordlist(t_word_list *star_node, t_word_list *node, char *file, t_data *d);

static bool	have_star(t_word_list *node)
{
	size_t	i;

	if (node->word == NULL)
		return (false);
	i = 0;
	while (node->word[i] != '\0')
	{
		if (node->word[i] == '*' && node->type[i] != IS_IN_QUOTED)
			return (true);
		i++;
	}
	return (false);
}

bool	only_stars(t_word_list *node)
{
	size_t	i;

	i = 0;
	while (node->word[i] != '\0')
	{
		if (node->word[i] != '*' || node->type[i] == IS_IN_QUOTED)
			return (false);
		i++;
	}
	return (true);
}

t_word_list	*expand_pathname_wordlist(t_word_list *head, t_word_list *node, t_data *d)
{
	DIR				*dirp;
	struct dirent	*entry;
	t_word_list		*star_node;

	if (!have_star(node))
		return (node->next);
	dirp = try_opendir(".", d);
	if (dirp == NULL)
		return (node->next);
	entry = try_readdir(dirp, d);
	star_node = node;
	while (entry != NULL)
	{
		if (*(entry->d_name) != '.')
			node = expand_star_wordlist(star_node, node, entry->d_name, d);
		entry = try_readdir(dirp, d);
	}
	if (star_node != node)
		word_list_delete_target(&head, star_node);
	return (node->next);
}
