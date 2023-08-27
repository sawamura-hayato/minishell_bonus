/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:35:53 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/27 15:35:19 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "init.h"
#include "library.h"
#include <stdlib.h>

static char	*export_make_str(char *str, t_envs *node)
{
	char	*new_str;

	new_str = try_strjoin_free(str, "declare -x ");
	new_str = try_strjoin_free(new_str, node->key);
	if (node->value == NULL)
		return (try_strjoin_free(new_str, "\n"));
	new_str = try_strjoin_free(new_str, "=\"");
	new_str = try_strjoin_free(new_str, node->value);
	return (try_strjoin_free(new_str, "\"\n"));
}

static void	export_put_str(char *str, t_data *d)
{
	if (str[0] != '\0')
		try_write(STDOUT_FILENO, str, ft_strlen(str), d);
	free(str);
}

static char	*export_str(t_envs *node, char *str, size_t loop_index)
{
	if (loop_index == 0 && ft_isupper(node->key[0]))
		str = export_make_str(str, node);
	else if (loop_index == 1 && ft_strcmp(node->key, "_") != 0
		&& node->key[0] == '_')
		str = export_make_str(str, node);
	else if (loop_index == 2 && ft_islower(node->key[0]))
		str = export_make_str(str, node);
	return (str);
}

void	export_show(t_data *d)
{
	t_envs	*node;
	char	*str;
	size_t	i;
	size_t	loop_index;

	str = try_strdup("");
	i = 0;
	loop_index = 0;
	while (i < HASHMAP_SIZE)
	{
		node = d->envs_hashmap[i];
		while (node != NULL)
		{
			str = export_str(node, str, loop_index);
			node = node->next;
		}
		i++;
		if (i == HASHMAP_SIZE && loop_index < 3)
		{
			i = 0;
			loop_index++;
		}
	}
	export_put_str(str, d);
}
