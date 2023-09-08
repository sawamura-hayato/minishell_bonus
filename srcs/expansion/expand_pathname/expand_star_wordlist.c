/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star_wordlist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:45:44 by tterao            #+#    #+#             */
/*   Updated: 2023/09/09 02:31:19 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

bool	expand_only_stars(t_word_list *node);

size_t	expand_get_star_index(const char *star_str, char *type, size_t i)
{
	char	*star;

	star = ft_strchr(&star_str[i], '*');
	if (star == NULL)
		return (0);
	i = star - star_str;
	if (type[i] != IS_IN_QUOTED)
		return (i);
	return (expand_get_star_index(star_str, type, i + 1));
}

bool	is_last_component_matching(char *star_comp, char *file)
{
	bool	is_match;
	char	*tmp;

	if (*star_comp == '\0')
	{
		free(star_comp);
		return (true);
	}
	tmp = file;
	while (ft_strstr(file, star_comp) != NULL)
	{
		tmp = file;
		file++;
	}
	file = tmp;
	is_match = ft_strcmp(star_comp, file);
	free(star_comp);
	return (is_match == 0);
}

bool	expand_star_loop(const char *star_str, char *type,
										char *file, size_t i)
{
	size_t	next_star;
	char	*star_comp;

	next_star = expand_get_star_index(star_str, type, i);
	if (next_star != 0)
		star_comp = try_substr(star_str, i, next_star - i);
	else if (i == 0 && star_str[i] == '*' && type[i] != IS_IN_QUOTED)
		return (expand_star_loop(star_str, type, file, next_star + 1));
	else
		return (is_last_component_matching(try_strdup(&star_str[i]), file));
	file = ft_strstr(file, star_comp);
	if (file != NULL)
		file += ft_strlen(star_comp);
	free(star_comp);
	if (file == NULL)
		return (false);
	return (expand_star_loop(star_str, type, file, next_star + 1));
}

static t_word_list	*newnode(const char *file, t_word_list *nextnode)
{
	t_word_list		*newnode;
	const size_t	len = ft_strlen(file);

	newnode = try_calloc(1, sizeof(t_word_list));
	newnode->tk_type = WORD;
	newnode->word = try_strdup(file);
	newnode->type = try_calloc(len + 1, sizeof(char));
	ft_memset(newnode->type, '1', len);
	newnode->next = nextnode;
	return (newnode);
}

t_word_list	*expand_star_wordlist(t_word_list *star_node, t_word_list *node,
									char *file)
{
	size_t	first_star_index;
	size_t	file_index;

	file_index = 0;
	if (expand_only_stars(star_node))
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
