/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname_wordlist.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:21:07 by tterao            #+#    #+#             */
/*   Updated: 2023/09/26 14:52:25 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"
#include <sys/types.h>
#include <dirent.h>

t_word_list	*expand_star_wordlist(t_word_list *star_node, t_word_list *node,
				char *file);

bool	expand_have_star_wordlist(t_word_list *node)
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

bool	expand_only_stars(t_word_list *node)
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

bool	expand_is_dot_dir(char *dirname)
{
	return ((ft_strcmp(dirname, ".") == 0 || ft_strcmp(dirname, "..") == 0));
}

t_word_list	*expand_pathname_wordlist(t_word_list **head, t_word_list *node,
									t_word_list **pre_node, t_data *d)
{
	DIR				*dirp;
	struct dirent	*entry;
	t_word_list		*star_node;

	*pre_node = node;
	if (!expand_have_star_wordlist(node))
		return (node->next);
	dirp = try_opendir(".", d);
	if (dirp == NULL)
		return (node->next);
	entry = try_readdir(dirp, d);
	star_node = node;
	while (entry != NULL)
	{
		if (!expand_is_dot_dir(entry->d_name)
			&& (*(star_node->word) == '.' || *(entry->d_name) != '.'))
			node = expand_star_wordlist(star_node, node, entry->d_name);
		entry = try_readdir(dirp, d);
	}
	try_closedir(dirp, d);
	if (star_node != node)
		word_list_delete_target(head, star_node);
	*pre_node = node;
	return (node->next);
}
