/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:06:19 by tterao            #+#    #+#             */
/*   Updated: 2023/08/08 18:42:17 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"

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

t_envs	*envs_get_node(char *_key, t_envs **envs_hashmap)
{
	t_envs	*node;

	node = envs_hashmap[envs_get_hashmap_index(_key[0])];
	while (node)
	{
		if (ft_strcmp(node->key, _key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	envs_init(const char **environ, t_data *d)
{
	d->envs_hashmap = try_calloc(HASHMAP_SIZE, sizeof(t_envs *));
	while (*environ != NULL)
	{
		envs_newnode(get_key(*environ), get_value(*environ), d->envs_hashmap);
		environ++;
	}
}

#include <stdio.h>
static void	debug_hashmap(t_envs **envs_hashmap)
{
	size_t	i = 0;
	t_envs	*node;
	while (i < HASHMAP_SIZE)
	{
		node = envs_hashmap[i];
		while (node)
		{
			printf("%s=%s\n", node->key, node->value);
			node = node->next;
		}
		i++;
	}
	printf("---------------------------------\n");
}

static void	debug_envp(char **envp)
{
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
	printf("---------------------------------\n");
}

int	main()
{
	t_data	d;

	extern const char	**environ;
	envs_init(environ, &d);
	debug_hashmap(d.envs_hashmap);
	envs_addstr("test", "test", d.envs_hashmap);
	envs_addstr("test", "test", d.envs_hashmap);
	envs_modify("test", "テスト", d.envs_hashmap);
	envs_modify("t", "tachu", d.envs_hashmap);
	// debug_hashmap(d.envs_hashmap);
	envs_delete("test", d.envs_hashmap);
	envs_delete("noexit", d.envs_hashmap);
	envs_delete("tachu", d.envs_hashmap);
	envs_delete("A", d.envs_hashmap);
	// debug_hashmap(d.envs_hashmap);
	debug_envp(envs_make_envp(d.envs_hashmap));
	return (0);
}
