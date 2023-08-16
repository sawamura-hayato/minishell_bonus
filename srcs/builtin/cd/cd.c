/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:06:35 by tterao            #+#    #+#             */
/*   Updated: 2023/08/16 15:54:42 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

static void	cd_nodir(t_data *d)
{
	t_envs		*node;
	const char	*msg = "cd: HOME not set\n";

	node = envs_get_node("HOME", d->envs_hashmap);
	if (node == NULL || node->value == NULL)
	{
		d->exit_status = EXIT_FAILURE;
		return (try_write(STDERR_FILENO, msg, ft_strlen(msg), d));
	}
	try_chdir(node->value, d);
}

static bool	cd_iserror(char **argv)
{
	size_t	size;

	size = 0;
	while (argv[size] != NULL)
		size++;
	return (size > 2);
}

static void	cd_put_error_too_many_args(t_data *d)
{
	const char	*msg = "cd: too many arguments\n";

	d->exit_status = EXIT_FAILURE;
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
}

void	builtin_cd(char **argv, t_data *d)
{
	const char	*msg;

	d->exit_status = EXIT_SUCCESS;
	if (cd_iserror(argv))
		return (cd_put_error_too_many_args(d));
	if (argv[1] == NULL)
		return (cd_nodir(d));
	try_chdir(argv[1], d);
}
