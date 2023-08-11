/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:35:53 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/11 15:20:06 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "init.h"
#include "library.h"
#include <stdlib.h>

static char	*export_strjoin(char *str1, const char *str2)
{
	char	*new_str;

	new_str = try_strjoin(str1, str2);
	free(str1);
	return (new_str);
}

static char	*export_make_str(char *str, t_envs *node)
{
	char	*new_str;
	
	new_str = export_strjoin(str, "declare -x ");
	new_str = export_strjoin(new_str, node->key);
	if (node->value == NULL)
		return (export_strjoin(new_str, "\n"));
	new_str = export_strjoin(new_str, "=\"");
	new_str = export_strjoin(new_str, node->value);
	return (export_strjoin(new_str, "\"\n"));
}

static void	export_put_str(char *str)
{
	if (str[0] == '\0')
		try_write(STDOUT_FILENO, "\n", 1);
	else
		try_write(STDOUT_FILENO, str, ft_strlen(str));
	free(str);
}

static char	*export_str(t_envs *node, char *str, size_t loop_index)
{
	if (loop_index == 0 && ft_isupper(node->key[0]))
		str = export_make_str(str, node);
	else if (loop_index == 1 && node->key[0] == '_')
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
	export_put_str(str);
}
