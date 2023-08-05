/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:06:19 by tterao            #+#    #+#             */
/*   Updated: 2023/08/05 19:50:06 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdio.h>

static char	*get_key(const char *str)
{
	return (
		try_substr(
			str,
			0,
			(char *)ft_memchr(str, '=', ft_strlen(str)) - &str[0]
		));
}

static char	*get_value(const char *str)
{
	return (try_strdup((char *)ft_memchr(str, '=', ft_strlen(str)) + 1));
}

size_t	envs_get_hashmap_index(char alpha)
{
	size_t	index;

	if (ft_isupper(alpha))
		index = alpha - 'A';
	else if (ft_islower(alpha))
		index = alpha - 'a';
	else
		index = UNDERLINE;
	return (index);
}

static void	insert_node(t_envs *new_node, t_envs **envs_hashmap)
{
	size_t	index;
	t_envs	*node;

	index = envs_get_hashmap_index(new_node->key[0]);
	if (envs_hashmap[index] == NULL
		|| ft_strcmp(new_node->key, envs_hashmap[index]->key) < 0)
	{
		new_node->next = envs_hashmap[index];
		envs_hashmap[index] = new_node;
		return ;
	}
	node = envs_hashmap[index];
	while (node->next != NULL)
	{
		if (ft_strcmp(new_node->key, node->next->key) < 0)
			break ;
		node = node->next;
	}
	new_node->next = node->next;
	node->next = new_node;
}

void	envs_newnode(char *_key, char *_value, t_envs **envs_hashmap)
{
	t_envs	*node;
	t_envs	*next_node;

	node = try_calloc(1, sizeof(t_envs));
	node->key = _key;
	node->value = _value;
	insert_node(node, envs_hashmap);
}

void	envs_init(const char **environ, t_data *d)
{
	d->envs_hashmap = try_calloc(HASHMAP_SIZE, sizeof(t_envs *));
	while (*environ)
	{
		envs_newnode(get_key(*environ), get_value(*environ), d->envs_hashmap);
		// printf("%s, %s, %s-\n", *environ, get_key(*environ), get_value(*environ));
		*environ++;
	}
}

int	main()
{
	t_data	d;

	extern char	**environ;
	envs_init(environ, &d);
	size_t	i = 0;
	t_envs	*node;
	while (i < HASHMAP_SIZE)
	{
		node = d.envs_hashmap[i];
		while (node)
		{
			printf("%s=%s\n", node->key, node->value);
			node = node->next;
		}
		i++;
	}
}
