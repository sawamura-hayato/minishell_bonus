/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:06:19 by tterao            #+#    #+#             */
/*   Updated: 2023/08/10 18:19:10 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>

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

static char	*get_shlvl_value(char *value)
{
	const char	*msg = "warning: shell level (1000) too high, resetting to 1\n";
	int			shlvl;

	shlvl = ft_atoi(value);
	free(value);
	if (shlvl == 999)
	{
		try_write(STDOUT_FILENO, msg, ft_strlen(msg));
		return (try_itoa(1));
	}
	else
		return (try_itoa(++shlvl));

}

static void	init_three_envs(t_data *d)
{
	if (envs_get_node("OLDPWD", d->envs_hashmap) == NULL)
		envs_newnode(try_strdup("OLDPWD"), NULL, d->envs_hashmap);
	if (envs_get_node("PWD", d->envs_hashmap) == NULL)
		envs_newnode(try_strdup("PWD"), getcwd(NULL, 0), d->envs_hashmap);
	if (envs_get_node("SHLVL", d->envs_hashmap) == NULL)
		envs_newnode(try_strdup("SHLVL"), try_strdup("1"), d->envs_hashmap);
}

void	envs_init(const char **environ, t_data *d)
{
	char		*key;
	char		*value;

	d->envs_hashmap = try_calloc(HASHMAP_SIZE, sizeof(t_envs *));
	while (*environ != NULL)
	{
		key = get_key(*environ);
		value = get_value(*environ);
		if (ft_strcmp(key, "SHLVL") == 0)
			value = get_shlvl_value(value);
		envs_newnode(key, value, d->envs_hashmap);
		environ++;
	}
	init_three_envs(d);
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
	// envs_addstr("test", "test", d.envs_hashmap);
	// envs_addstr("test", "test", d.envs_hashmap);
	// envs_modify("test", "テスト", d.envs_hashmap);
	// envs_modify("t", "tachu", d.envs_hashmap);
	// debug_hashmap(d.envs_hashmap);
	// envs_delete("test", d.envs_hashmap);
	// envs_delete("noexit", d.envs_hashmap);
	// envs_delete("tachu", d.envs_hashmap);
	// envs_delete("A", d.envs_hashmap);
	// debug_hashmap(d.envs_hashmap);
	debug_envp(envs_make_envp(d.envs_hashmap));
	return (0);
}
