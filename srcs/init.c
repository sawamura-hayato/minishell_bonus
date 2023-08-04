/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:06:19 by tterao            #+#    #+#             */
/*   Updated: 2023/08/04 21:10:18 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdio.h>

static char	*get_key(char *str)
{
	return (
		try_substr(
			str,
			0,
			(char *)ft_memchr(str, '=', ft_strlen(str)) - &str[0]
		));
}

static char	*get_value(char *str)
{
	return (try_strdup((char *)ft_memchr(str, '=', ft_strlen(str)) + 1));
}

static t_envs	*insert_node(t_envs *new_node, t_envs **envs_hashmap)
{
	size_t	index;
	t_envs	*node;
	t_envs	*prev_node;

	if (ft_isupper(new_node->key[0]))
		index = new_node->key[0] - 'A';
	else if (ft_islower(new_node->key[0]))
		index = new_node->key[0] - 'a';
	else
		index = 26;
	if (envs_hashmap[index] == NULL
		|| ft_strcmp(new_node->key, envs_hashmap[index] < 0))
	{
		new_node->next = envs_hashmap[index];
		envs_hashmap[index] = new_node;
	}
	node = envs_hashmap[index];
	while (node)
	{
		if (ft_strcmp(new_node->key, node->next) < 0)
		node = node->next;
	}

}

// A ABC ACC

// ABB
// envs_hashmap[0] = node;


void	envs_newnode(char *_key, char *_value, t_envs **envs_hashmap)
{
	t_envs	*node;
	t_envs	*next_node;

	node = try_calloc(1, sizeof(t_envs));
	node->key = _key;
	node->value = _value;
	insert_node(node, envs_hashmap);

}

void	envs_init(const char **environ, t_data d)
{
	d.envs_hashmap = try_calloc(27, sizeof(t_envs));
	while (*environ)
	{
		envs_newnode(get_key(*environ), get_value(*environ), d.envs_hashmap);
		printf("%s, %s, %s-\n", *environ, get_key(*environ), get_value(*environ));
		*environ++;
	}
}

int	main()
{
	t_data	d;

	extern char	**environ;
	envs_init(environ, d);
}
