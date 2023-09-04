/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname_wordlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:29:27 by tterao            #+#    #+#             */
/*   Updated: 2023/09/04 14:39:44 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"
#include <sys/types.h>
#include <dirent.h>

t_word_list	*expand_star_wordlist(t_word_list *star_node, t_word_list *node, const char *file, t_data *d);

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

void	expand_pathname_wordlist(t_word_list *node, t_data *d)
{
	DIR				*dirp;
	struct dirent	*entry;
	t_word_list		*star_node;

	if (!have_star(node))
		return ;
	dirp = try_opendir(".", d);
	if (dirp == NULL)
		return ;
	entry = try_readdir(dirp, d);
	star_node = node;
	while (entry != NULL)
	{
		if (*(entry->d_name) != '.')
			node = expand_star_wordlist(star_node, node, entry->d_name, d);
		entry = try_readdir(dirp, d);
	}
	// 展開された場合、元の＊のnodeを削除する
	// delete_node();
}
