/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:06:19 by tterao            #+#    #+#             */
/*   Updated: 2023/09/20 15:00:38 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>
#define SHLVL_MAX_VALUE 999

bool	envs_is_invalid_key(const char *str);

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
	if (shlvl == SHLVL_MAX_VALUE)
	{
		try_write(STDOUT_FILENO, msg, ft_strlen(msg), d);
		return (try_itoa(1));
	}
	else
		return (try_itoa(++shlvl));
}

static void	init_three_envs(t_data *d)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror(
			"shell-init: error retrieving current directory: "
			"getcwd: cannot access parent directories");
	}
	if (envs_get_node("OLDPWD", d->envs_hashmap) == NULL)
		envs_newnode(try_strdup("OLDPWD"), NULL, d->envs_hashmap);
	if (cwd != NULL && envs_get_node("PWD", d->envs_hashmap) == NULL)
		envs_newnode(try_strdup("PWD"), try_strdup(cwd), d->envs_hashmap);
	if (envs_get_node("SHLVL", d->envs_hashmap) == NULL)
		envs_newnode(try_strdup("SHLVL"), try_strdup("1"), d->envs_hashmap);
	d->pwd = cwd;
	d->oldpwd = envs_get_value("OLDPWD", d->envs_hashmap);
}

void	envs_init(const char **environ, t_data *d)
{
	char		*key;
	char		*value;

	d->envs_hashmap = try_calloc(HASHMAP_SIZE, sizeof(t_envs *));
	while (*environ != NULL)
	{
		if (ft_memchr(*environ, '=', ft_strlen(*environ)) != NULL
			&& !envs_is_invalid_key(*environ))
		{
			key = get_key(*environ);
			value = get_value(*environ);
			if (ft_strcmp(key, "SHLVL") == 0)
				value = get_shlvl_value(value, d);
			envs_newnode(key, value, d->envs_hashmap);
		}
		environ++;
	}
	init_three_envs(d);
}
