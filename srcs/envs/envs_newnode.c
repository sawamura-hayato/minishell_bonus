/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_newnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:43:48 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/31 17:15:31 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>

t_envs	*envs_get_node(const char *_key, t_envs **envs_hashmap)
{
	t_envs	*node;

	node = envs_hashmap[envs_get_hashmap_index(_key[0])];
	while (node != NULL)
	{
		if (ft_strcmp(node->key, _key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
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

	node = envs_get_node(_key, envs_hashmap);
	if (node != NULL)
	{
		free(_key);
		if (_value == NULL && node->value != NULL)
			return ;
		free(node->value);
		node->value = _value;
	}
	else
	{
		node = try_calloc(1, sizeof(t_envs));
		node->key = _key;
		node->value = _value;
		insert_node(node, envs_hashmap);
	}
}
