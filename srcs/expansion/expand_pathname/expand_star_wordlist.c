/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star_wordlist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:45:44 by tterao            #+#    #+#             */
/*   Updated: 2023/09/04 20:17:06 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

bool	only_stars(t_word_list *node);

static size_t	get_star_index(const char *star_str, char *type, size_t i)
{
	char	*star;
	size_t	add_index;

	star = ft_strchr(&star_str[i], '*');
	if (star == NULL)
		return (0);
	add_index = star - &star_str[i];
	if (type[i + add_index] != IS_IN_QUOTED)
		return (add_index + i);
	// if (add_index == 0)
	// 	add_index++;
	printf("strstr%s\n", &star_str[add_index + i]);
	return (get_star_index(star, type, add_index + i));
}

bool	is_last_component_matching(char *star_comp, char *file)
{
	bool	is_match;
	char	*tmp;

	if (*star_comp == '\0')
		return (true);
	tmp = file;
	printf("sarcomp=%s\n", star_comp);
	while (ft_strstr(file, star_comp) != NULL)
	{
		tmp = file;
		file++;
	}
	file = tmp;
	printf("star=%s\n", star_comp);
	printf("file=%s\n\n", file);
	is_match = ft_strcmp(star_comp, file);
	free(star_comp);
	return (is_match == 0);
}

static bool	expand_star_wordlist_loop(const char *star_str, char *type, char *file, size_t i)
{
	size_t	next_star;
	char	*star_comp;

	next_star = get_star_index(star_str, type, i);
	// if (next_star != 0 && (next_star - i) == 1)
	// 	return (expand_star_wordlist_loop(star_str, type, file, next_star + 1));
	if (next_star != 0)
		star_comp = try_substr(star_str, i, next_star - i);
	else
		return (is_last_component_matching(try_strdup(&star_str[i]), file));
	// printf("star str=%s\n", star_str);
	printf("i=%zu next=%zu\n", i, next_star);
	printf("loop star=%s\n", star_comp);
	printf("loop file=%s\n\n", file);
	file = ft_strstr(file, star_comp);
	if (file != NULL)
		file += ft_strlen(star_comp);
	free(star_comp);
	if (file == NULL)
		return (false);
	return (expand_star_wordlist_loop(star_str, type, file, next_star + 1));
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

t_word_list	*expand_star_wordlist(t_word_list *star_node, t_word_list *node, char *file, t_data *d)
{
	size_t	first_star_index;

	(void)d;
	if (only_stars(star_node))
	{
		node->next = newnode(file, node->next);
		return (node->next);
	}
	first_star_index = get_star_index(star_node->word, (char *)file, 0);
	if (star_node->word[0] == '*')
		first_star_index = 1;
	else if (ft_strncmp(star_node->word, file, first_star_index - 1) != 0)
		return (node);
	if (expand_star_wordlist_loop(star_node->word, star_node->type,
			&file[first_star_index], first_star_index + 1))
	{
		node->next = newnode(file, node->next);
		node = node->next;
	}
	return (node);
}
