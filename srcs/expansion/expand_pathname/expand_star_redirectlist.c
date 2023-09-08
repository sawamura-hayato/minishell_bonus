/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star_redirectlist.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:24:30 by tterao            #+#    #+#             */
/*   Updated: 2023/09/09 02:33:42 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_star_loop(const char *star_str, char *type,
			char *file, size_t i);
size_t	expand_get_star_index(const char *star_str, char *type, size_t i);

static t_redirect_list	*newnode(const char *file, t_redirect_list *nextnode)
{
	t_redirect_list	*newnode;
	const size_t	len = ft_strlen(file);

	newnode = try_calloc(1, sizeof(t_redirect_list));
	newnode->re_type = PS_FILE;
	newnode->word = try_strdup(file);
	newnode->type = try_calloc(len + 1, sizeof(char));
	ft_memset(newnode->type, '1', len);
	newnode->next = nextnode;
	return (newnode);
}

static bool	only_stars(t_redirect_list *node)
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

t_redirect_list	*expand_star_redirectlist(t_redirect_list *star_node,
				t_redirect_list *node, char *file)
{
	size_t	first_star_index;
	size_t	file_index;

	file_index = 0;
	if (only_stars(star_node))
	{
		node->next = newnode(file, node->next);
		return (node->next);
	}
	first_star_index = expand_get_star_index(star_node->word, star_node->type, 0);
	if (first_star_index != 0
		&& ft_strncmp(star_node->word, file, first_star_index) != 0)
		return (node);
	if (first_star_index != 0)
	{
		file_index = first_star_index;
		first_star_index++;
	}
	if (expand_star_loop(star_node->word, star_node->type,
			&file[file_index], first_star_index))
	{
		node->next = newnode(file, node->next);
		node = node->next;
	}
	return (node);
}
