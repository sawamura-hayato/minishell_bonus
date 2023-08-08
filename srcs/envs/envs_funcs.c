/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:53:37 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/08 16:50:32 by tatyu            ###   ########.fr       */
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
		node->value = try_strdup(new_value);
	}
	else
		envs_newnode(try_strdup(_key), try_strdup(new_value), envs_hashmap);
}

void	envs_addstr(char *_key, char *adding_value, t_envs **envs_hashmap)
{
	t_envs	*node;
	char	*new_value;
	
	node = envs_get_node(_key, envs_hashmap);
	if (node != NULL)
	{
		new_value = try_strjoin(node->key, adding_value);
		free(node->value);
		node->value = new_value;
	}
	else
		envs_newnode(try_strdup(_key), try_strdup(adding_value), envs_hashmap);
}

void	envs_delete(char *_key, t_envs **envs_hashmap)
{
	t_envs	*node;

	node = envs_hashmap[envs_get_hashmap_index(_key[0])];
	if (node == NULL || ft_strcmp(node->key, _key) == 0)
	{
		envs_hashmap[envs_get_hashmap_index(_key[0])] = NULL;
		envs_free_node(node);
		return ;
	}
	while (node->next)
	{
		if (ft_strcmp(node->next->key, _key) == 0)
		{
			node->next = (node->next)->next;
			envs_free_node(node->next);
		}
		node = node->next;
	}
}

void	envs_free_node(t_envs *node)
{
	free(node->key);
	free(node->value);
	free(node);
}
