/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:42:15 by tterao            #+#    #+#             */
/*   Updated: 2023/09/03 21:44:58 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

# define IS_IN_QUOTED '4'
static size_t	*get_star_index(char *star_str, char *type, size_t i)
{
	char	*star;

	star = ft_strchr(&star_str[i], '*');
	if (star == NULL)
		return (0);
	i = star - &star_str[i];
	type += i;
	if (type != IS_IN_QUOTED)
		return (i);
	return (get_star_index(star, type, i));
}

static bool	expand_star_loop(const char *star_str, char *type, char *file, size_t i)
{
	size_t	next_star;
	char	star_comp;

	next_star = get_star_index(star_str, type, i);
	if (next_star != 0)
		star_comp = try_substr(star_str, i, next_star - i);
	else
		star_comp = try_strdup(&star_str[i]);
	file = ft_strstr(file, star_comp);
	free(star_comp);
	if (file == NULL)
		return (false);
	if (next_star == 0)
		return (true);
	return (expand_star_loop(star_str, type, file, i));
}

void	expand_star(t_word_list *node, const char *file, t_data *d)
{
	size_t	first_star_index;
	char	*first_star;

	first_star_index = get_star_index(node->word, file, 0);
	if (node->word[0] == '*')
		first_star_index = 1;
	else if (ft_strncmp(node->word, file, first_star_index) != 0)
		return ;
	if (expand_star_loop(node->word, node->type, (char *)file, first_star_index))
		node->next = newnode();
}
