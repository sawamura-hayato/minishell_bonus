/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname_redirectlist.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:02:30 by tterao            #+#    #+#             */
/*   Updated: 2023/09/05 15:08:10 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_redirect_list	*expand_star_redirectlist(t_redirect_list *star_node,
					t_redirect_list *node, char *file);

static bool	expand_have_star_redirectlist(t_redirect_list *node)
{
	size_t	i;

	if (node->word == NULL || node->re_type != PS_FILE)
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

static bool	expand_eachfile(DIR *dirp, struct dirent *entry,
					t_redirect_list *star_node, t_data *d)
{
	t_redirect_list		*node;
	t_redirect_list		*tmp;
	size_t				expand_cnt;

	node = star_node;
	expand_cnt = 0;
	while (entry != NULL)
	{
		tmp = node;
		if (*(entry->d_name) != '.')
			node = expand_star_redirectlist(star_node, node, entry->d_name);
		if (tmp != node)
			expand_cnt++;
		if (expand_cnt == 2)
			return (false);
		entry = try_readdir(dirp, d);
	}
	return (true);
}

static void	delete_expanded_nodes(t_redirect_list **head, t_redirect_list *node)
{
	node->is_ambiguous_error = true;
	redirect_delete_target(head, node->next);
	redirect_delete_target(head, node->next);
}

t_redirect_list	*expand_pathname_redirectlist(t_redirect_list *head,
					t_redirect_list *node, t_data *d)
{
	DIR					*dirp;
	struct dirent		*entry;
	t_redirect_list		*tmp;

	if (!expand_have_star_redirectlist(node))
		return (node->next);
	dirp = try_opendir(".", d);
	if (dirp == NULL)
		return (node->next);
	entry = try_readdir(dirp, d);
	if (expand_eachfile(dirp, entry, node, d))
	{
		tmp = node->next;
		redirect_delete_target(&head, node);
		node = tmp;
	}
	else
		delete_expanded_nodes(&head, node);
	return (node->next);
}
