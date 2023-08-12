/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:06:19 by tterao            #+#    #+#             */
/*   Updated: 2023/08/12 20:21:28 by tterao           ###   ########.fr       */
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

static char	*get_shlvl_value(char *value, t_data *d)
{
	const char	*msg = "warning: shell level (1000) too high, resetting to 1\n";
	int			shlvl;

	shlvl = ft_atoi(value);
	free(value);
	if (shlvl == 999)
	{
		try_write(STDOUT_FILENO, msg, ft_strlen(msg), d);
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
			value = get_shlvl_value(value, d);
		envs_newnode(key, value, d->envs_hashmap);
		environ++;
	}
	init_three_envs(d);
}

// #include <stdio.h>
// static void	debug_hashmap(t_envs **envs_hashmap)
// {
// 	size_t	i = 0;
// 	t_envs	*node;
// 	while (i < HASHMAP_SIZE)
// 	{
// 		node = envs_hashmap[i];
// 		while (node)
// 		{
// 			printf("%s=%s\n", node->key, node->value);
// 			node = node->next;
// 		}
// 		i++;
// 	}
// 	printf("---------------------------------\n");
// }

// static void	debug_envp(char **envp)
// {
// 	while (*envp != NULL)
// 	{
// 		printf("%s\n", *envp);
// 		envp++;
// 	}
// 	printf("---------------------------------\n");
// }

// #include "builtins.h"
// #include <stdio.h>

// int	main()
// {
// 	t_data	d;

// 	extern const char	**environ;
// 	envs_init(environ, &d);
// 	builtin_export((char *[]){"export", NULL}, &d);
// 	printf("------------------------------------------------------------------------------------------------------------------------------------\n");
// 	builtin_export((char *[]){"export", "test=test", "a=abc", NULL}, &d);
// 	builtin_export((char *[]){"export", NULL}, &d);
// 	printf("------------------------------------------------------------------------------------------------------------------------------------\n");

// 	builtin_export((char *[]){"export", "test+=", "a+=", "*fea", "b", "a", NULL}, &d);
// 	// builtin_export((char *[]){"export", "test=", "a+=abc", NULL}, &d);
// 	builtin_export((char *[]){"export", NULL}, &d);
// 	printf("------------------------------------------------------------------------------------------------------------------------------------\n");
// 	builtin_export((char *[]){"export", "+=test", "op=========", "o+=====", "c", "d", "e", "f", "g", NULL}, &d);
// 	builtin_export((char *[]){"export", NULL}, &d);


// 	return (0);
// }
