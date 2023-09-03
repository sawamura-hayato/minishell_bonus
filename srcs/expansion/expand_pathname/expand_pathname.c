/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:29:27 by tterao            #+#    #+#             */
/*   Updated: 2023/09/03 21:06:26 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"
#include <sys/types.h>
#include <dirent.h>

# define IS_IN_QUOTED '4'
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

void	expand_pathname(t_word_list *node, t_data *d)
{
	DIR				*dirp;
	struct dirent	*entry;

	expand_delete_quotation_word_list(node);
	if (!have_star(node))
		return ;
	dirp = try_opendir(".", d);
	entry = try_readdir(dirp, d);
	while (entry != NULL)
	{
		if (*(entry->d_name) != '.')
			expand_star(node, entry->d_name, d);
		entry = try_readdir(dirp, d);
	}
	// 展開された場合、元の＊のnodeを削除する
	// delete_node();
}
