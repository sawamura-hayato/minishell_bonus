/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:01:02 by tterao            #+#    #+#             */
/*   Updated: 2023/08/27 15:25:32 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

static void	env_put_error(char *str, t_data *d)
{
	char	*msg;

	d->exit_status = EXIT_FAILURE;
	msg = try_strjoin_free(try_strdup("env: `"), str);
	msg = try_strjoin_free(msg, "\': not a valid argument\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
}

static char	*make_str(char *str, t_envs *node)
{
	str = try_strjoin_free(str, node->key);
	str = try_strjoin_free(str, "=");
	str = try_strjoin_free(str, node->value);
	str = try_strjoin_free(str, "\n");
	return (str);
}

static void	put_str(char *str, t_data *d)
{
	if (str[0] != '\0')
		try_write(STDOUT_FILENO, str, ft_strlen(str), d);
	free(str);
}

void	builtin_env(char **argv, t_data *d)
{
	size_t	i;
	t_envs	*node;
	char	*str;

	d->exit_status = EXIT_SUCCESS;
	if (argv[1] != NULL)
		return (env_put_error(argv[1], d));
	i = 0;
	str = try_strdup("");
	while (i < HASHMAP_SIZE)
	{
		node = d->envs_hashmap[i];
		while (node != NULL)
		{
			if (node->value != NULL)
				str = make_str(str, node);
			node = node->next;
		}
		i++;
	}
	put_str(str, d);
}
