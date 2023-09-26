/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_make_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:13:29 by tatyu             #+#    #+#             */
/*   Updated: 2023/09/26 14:06:39 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>

bool	export_is_symbol(char c);

static size_t	get_envs_num(t_envs **envs_hashmap)
{
	size_t	i;
	size_t	num;
	t_envs	*node;

	i = 0;
	num = 0;
	while (i < HASHMAP_SIZE)
	{
		node = envs_hashmap[i];
		while (node != NULL)
		{
			if (node->value != NULL)
				num++;
			node = node->next;
		}
		i++;
	}
	return (num);
}

static char	*make_str_with_keyvalue(t_envs *node)
{
	char	*key_value;
	char	*tmp;

	tmp = try_strjoin(node->key, "=");
	key_value = try_strjoin(tmp, node->value);
	free(tmp);
	return (key_value);
}

bool	envs_is_invalid_key(const char *str)
{
	if (ft_isdigit(*str) || *str == '+' || *str == '=')
		return (true);
	while (*str != '=' && *str != '\0')
	{
		if (export_is_symbol(*str) || ft_isspace(*str))
			return (true);
		str++;
	}
	return (false);
}

char	**envs_make_envp(t_envs **envs_hashmap)
{
	size_t	hm_i;
	size_t	envp_i;
	char	**envp;
	t_envs	*node;

	envp = try_calloc(get_envs_num(envs_hashmap) + 1, sizeof(char *));
	hm_i = 0;
	envp_i = 0;
	while (hm_i < HASHMAP_SIZE)
	{
		node = envs_hashmap[hm_i];
		while (node != NULL)
		{
			if (node->value != NULL)
			{
				envp[envp_i] = make_str_with_keyvalue(node);
				envp_i++;
			}
			node = node->next;
		}
		hm_i++;
	}
	return (envp);
}
