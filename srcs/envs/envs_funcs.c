/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:53:37 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/29 21:10:47 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>

void	envs_modify(char *_key, char *new_value, t_envs **envs_hashmap)
{
	t_envs	*node;

	node = envs_get_node(_key, envs_hashmap);
	if (node != NULL)
	{
		free(node->value);
		free(_key);
		node->value = new_value;
	}
	else
		envs_newnode(_key, new_value, envs_hashmap);
}

void	envs_addstr(char *_key, char *adding_value, t_envs **envs_hashmap)
{
	t_envs	*node;

	node = envs_get_node(_key, envs_hashmap);
	if (node != NULL)
	{
		node->value = try_strjoin_free(node->value, adding_value);
		free(_key);
		free(adding_value);
	}
	else
		envs_newnode(_key, adding_value, envs_hashmap);
}

void	envs_delete(char *_key, t_envs **envs_hashmap)
{
	t_envs	*node;
	t_envs	*target;

	node = envs_hashmap[envs_get_hashmap_index(_key[0])];
	if (node == NULL || ft_strcmp(node->key, _key) == 0)
	{
		envs_hashmap[envs_get_hashmap_index(_key[0])] = NULL;
		envs_free_node(node);
		return ;
	}
	while (node->next != NULL)
	{
		if (ft_strcmp((node->next)->key, _key) == 0)
		{
			target = node->next;
			node->next = target->next;
			envs_free_node(target);
			break ;
		}
		node = node->next;
	}
}

char	*envs_get_value(const char *_key, t_envs **envs_hashmap)
{
	t_envs	*target;

	target = envs_get_node(_key, envs_hashmap);
	if (target == NULL || target->value == NULL)
		return (NULL);
	return (try_strdup(target->value));
}

void	envs_free_node(t_envs *node)
{
	if (node == NULL)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}
